####################################################################################################
#
#   Copyright (c) 2021 - 2022, Networked Embedded Systems Lab, TU Dresden
#   All rights reserved.
#
#   Redistribution and use in source and binary forms, with or without
#   modification, are permitted provided that the following conditions are met:
#       * Redistributions of source code must retain the above copyright
#         notice, this list of conditions and the following disclaimer.
#       * Redistributions in binary form must reproduce the above copyright
#         notice, this list of conditions and the following disclaimer in the
#         documentation and/or other materials provided with the distribution.
#       * Neither the name of the NES Lab or TU Dresden nor the
#         names of its contributors may be used to endorse or promote products
#         derived from this software without specific prior written permission.
#
#   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
#   ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
#   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
#   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
#   DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
#   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
#   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
#   ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
#   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
#   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
####################################################################################################
#
#   @file                   glue_config.py
#
#   @brief                  Glue config file that provides support for TrafficBench data in Glue
#                           (loader, auto-linker, viewer). For details see
#                           https://docs.glueviz.org/en/stable/customizing_guide/customization.html
#
#   @version                $Id$
#   @date                   TODO
#
#   @author                 Carsten Herrmann
#
####################################################################################################

from glue.core import Data
from glue.core.component_link import ComponentLink
from glue.core.component_id import ComponentID
from glue.core.subset import RangeSubsetState
from glue.config import data_factory
from glue.config import autolinker
from glue import custom_viewer

import numpy as np
import tables as tbl
import base64
import matplotlib as mpl

####################################################################################################

product_name = "TrafficBench"

trx_loader_info = {"markers" : {}}

# PyTables enum types
TRX_Operation = tbl.Enum({'RX' : 0, 'TX' : 1})

# set TeX system used to save plots in PDF and PGF format
mpl.rcParams['pgf.texsystem'] = 'pdflatex'

####################################################################################################

# flatten nested structure by patching its dtype (without touching the data itself)
# This function is similar to numpy.lib.recfunctions.flatten_descr(), the main difference is
# that it also extends the field names (and the type of the return value).
def flatten_dtype(dtype, sep="_", prefix=""):
    assert(dtype.alignment == 1)
    if dtype.names is None:
        desc = [(prefix, dtype)]
    else:
        desc = []
        for name in dtype.names:
            (type_, _) = dtype.fields[name]
            name = prefix + name
            if type_.names is None:
#                 assert(type_.alignment == 1)
                desc.append((name, type_))
            else:
                desc.extend(flatten_dtype(type_, prefix = name + sep))
    return desc if prefix else np.dtype(desc)

####################################################################################################
# conversion functions, can be used as link functions

def power_db_to_linear(power_dB):
    return 10.0 ** (power_dB * 0.1)

def power_linear_to_db(power):
    return 10.0 * np.log10(power)

def gts_ticks_to_us(gts):
    TICKS_PER_US = 16
    return gts / TICKS_PER_US

def gts_us_to_ticks(gts):
    TICKS_PER_US = 16
    return np.int64(np.rint(gts * TICKS_PER_US))

def gts_ticks_to_s(gts):
    return gts_ticks_to_us(gts) / 1e6

def gts_s_to_ticks(gts):
    return gts_us_to_ticks(gts * 1e6)

# can be used to generate "unavailable" components (e.g. to enable "mixed" plots as in rx_viewer)
def const_nan(x):
    return np.full(x.shape, np.nan, dtype=np.float16)

####################################################################################################
# helper functions used for gts + node_id links

def src_id(id, op):
    x = id.astype(np.int16, copy=True)
    x[op != TRX_Operation.TX] = -1
    return x

def dst_id(id, op):
    x = id.astype(np.int16, copy=True)
    x[op != TRX_Operation.RX] = -1
    return x

def node_key(gts, id):
    gts = np.full(1, gts) if np.isscalar(gts) else gts
    x = np.full(len(gts), -1, dtype=np.float64)
    if not np.isscalar(id):
        assert(len(id) == len(gts))
        mask = (id >= 0)
        x[mask] = (id[mask] / 100000) + gts[mask]
    elif id >= 0:
        x = (id / 100000) + gts
    return x

####################################################################################################
# custom TRX loader
# for details, see
# <https://docs.glueviz.org/en/stable/customizing_guide/customization.html#custom-data-loaders>

def is_trx(filename, **kwargs):
    return filename.endswith('.h5')
    # TODO: improve detection

# note: default HDF5 reader has priority 100
@data_factory(product_name + " TRX loader", is_trx, priority=10000)
def read_trx(file_name):

    global trx_loader_info

    data = []
    with tbl.open_file(file_name, mode="r") as h5file:

        # check enum types        
        assert(TRX_Operation == h5file.root.trx_data.trx.get_enum('operation'))

        path_to_label = {
            "/trx_data/trx"             : "trx",
            "/catalogs/nodes"           : "nodes",
            "/catalogs/link_matrix"     : "link_matrix",
            "/catalogs/link_matrix_dBm" : "link_matrix_dBm",
            "/catalogs/transactions"    : "transactions",
            "/catalogs/rx_info"         : "rx_info",
        }

        # do simple straight-forward imports

        nodes = h5file.root.catalogs.nodes.read()
        data.append(Data(label=path_to_label["/catalogs/nodes"], node_id=nodes))
        
        t = h5file.root.catalogs.transactions.read()
        data.append(Data(label=path_to_label["/catalogs/transactions"], **dict(map(lambda x: (x, t[x]), t.dtype.names))))
    
        t = h5file.root.catalogs.rx_info.read()
        data.append(Data(label=path_to_label["/catalogs/rx_info"], **dict(map(lambda x: (x, t[x]), t.dtype.names))))
        rx_info = data[-1]
        rxi_array = t

        t = h5file.root.catalogs.link_matrix.read()
        data.append(Data(label=path_to_label["/catalogs/link_matrix"], rx_power=t))
        t = h5file.root.catalogs.link_matrix_dBm.read()
        data.append(Data(label=path_to_label["/catalogs/link_matrix_dBm"], rx_power=t))

        t = h5file.root.trx_data.trx.read()
        t.dtype = flatten_dtype(t.dtype, sep=":")
        data.append(Data(label=path_to_label["/trx_data/trx"], **dict(map(lambda x: (x, t[x]), t.dtype.names))))
        trx = data[-1]
        trx_array = t

        # import marker tables
        # store extra information in trx_loader_info, which can be evaluated by the auto-linker later on
        trx_loader_info["markers"] = {}
        for x in h5file.walk_nodes(where="/markers", classname="Table"):
            label = "markers : " + x._v_name
            t = x.read()
            data.append(Data(label=label, **dict(map(lambda x: (x, t[x]), t.dtype.names))))
            trx_loader_info["markers"][label] = (path_to_label[x._f_getattr("TABLE")], x._f_getattr("NODE_ID_FIELD"))


        # add source/destination_node_id fields to trx data
        # these fields simplify linking with rx_info
        # NOTE: With glueziv 1.2.x joins on multiple components are slow (explicitly mentioned in
        # <https://docs.glueviz.org/en/stable/api/glue.core.data.Data.html#glue.core.data.Data.join_on_key>).
        # It seems that this also holds for simple but derived components. We work around that by adding
        # "real" Components instead of DerivedComponents (using add_component() instead of add_component_link()).
        # Further, we provide additional source/destination_node_key fields that enable single component joins
        # by explicitly combining source/destination_node_id with schedule_gts.

        trx.add_component(src_id(trx["node_id"], trx["operation"]), "source_node_id")
        trx.add_component(dst_id(trx["node_id"], trx["operation"]), "destination_node_id")
        trx.add_component(node_key(trx["schedule_gts"], trx["source_node_id"]), "source_node_key")
        trx.add_component(node_key(trx["schedule_gts"], trx["destination_node_id"]), "destination_node_key")
        # trx.add_component_link(ComponentLink([trx.id["node_id"], trx.id["operation"]], ComponentID("source_node_id"), using=src_id))
        # trx.add_component_link(ComponentLink([trx.id["node_id"], trx.id["operation"]], ComponentID("destination_node_id"), using=dst_id))
        # trx.add_component_link(ComponentLink([trx.id["schedule_gts"], trx.id["source_node_id"]], ComponentID("source_node_key"), using=node_key))
        # trx.add_component_link(ComponentLink([trx.id["schedule_gts"], trx.id["destination_node_id"]], ComponentID("destination_node_key"), using=node_key))

        rx_info.add_component(node_key(rx_info["schedule_gts"], rx_info["source_node_id"]), "source_node_key")
        rx_info.add_component(node_key(rx_info["schedule_gts"], rx_info["destination_node_id"]), "destination_node_key")
        # rx_info.add_component_link(ComponentLink([rx_info.id["schedule_gts"], rx_info.id["source_node_id"]], ComponentID("source_node_key"), using=node_key))
        # rx_info.add_component_link(ComponentLink([rx_info.id["schedule_gts"], rx_info.id["destination_node_id"]], ComponentID("destination_node_key"), using=node_key))


        # import RSSI data

        trx_rssi = trx_array[trx_array["rssi:num_samples"] > 0]
        TICKS_PER_SAMPLE = 16

        # read samples, add anchor_offset field
        x = h5file.root.trx_data.rssi_data.read()
        s = np.array([], dtype=[("samples", x.dtype), ("anchor_offset", "uint16")])
        s = np.resize(s, len(x))
        s['samples'] = x

        # compute anchor_offsets
        for i in trx_rssi:
            a = i["rssi:data_anchor"]
            n = i["rssi:num_samples"]
            s["anchor_offset"][a:(a+n)] = np.arange(0,n)

        # add plain RSSI data object
        data.append(Data(label="rssi_data", **dict(map(lambda x: (x, s[x]), s.dtype.names))))
        rssi_data = data[-1]
        rssi_data["anchor"] = rssi_data.coordinate_components[0] - rssi_data.id["anchor_offset"]

        # add RSSI-by-node data objects
        x = np.array([], dtype=[
            ("rssi_dBm", s["samples"].dtype),
            # ("rssi_error", (np.float32, 2)),
            ("gts", trx["schedule_gts"].dtype),
            ("schedule_gts", trx["schedule_gts"].dtype),
            ("destination_node_key", trx["destination_node_key"].dtype)
            ])
        x = np.resize(x, len(s))
        for n in nodes:
            tn = trx_rssi[trx_rssi["node_id"] == n]
            if len(tn):
                nused = 0
                for tt in tn:
                    i = int(tt["rssi:data_anchor"])
                    k = int(tt["rssi:num_samples"])
                    xx = x[nused : nused + k]
                    xx["rssi_dBm"] = s["samples"][i : i + k]
                    # xx["rssi_error"] = 0.5
                    xx["schedule_gts"] = tt["schedule_gts"]
                    xx["gts"] = tt["schedule_gts"] + tt["rssi:end_lts"] - tt["schedule_lts"] + (np.arange(-k,0) + 1) * TICKS_PER_SAMPLE
                    xx["destination_node_key"] = node_key(tt["schedule_gts"], n)
                    nused += k
                xx = x[0:nused].copy()
                data.append(Data(label=f"rssi_{n}", **dict(map(lambda n: (n, xx[n]), xx.dtype.names))))
                xx = data[-1]

                xx.add_component_link(ComponentLink([xx.id["rssi_dBm"]], ComponentID("rssi_mW"), 
                    using=power_db_to_linear, inverse=power_linear_to_db))
                xx.add_component_link(ComponentLink([xx.id["gts"]], ComponentID("gts_us"), 
                    using=gts_ticks_to_us, inverse=gts_us_to_ticks))
                xx.add_component_link(ComponentLink([xx.id["gts"]], ComponentID("gts_s"), 
                    using=gts_ticks_to_s, inverse=gts_s_to_ticks))

                # add dummy components to establish "viewer compatibility" with bitstream data
                # NOTE: the source for const_nan() is a dummy, so any field can be used
                xx.add_component_link(ComponentLink([xx.id["schedule_gts"]], ComponentID("rx_symbol"), using=const_nan))
                xx.add_component_link(ComponentLink([xx.id["schedule_gts"]], ComponentID("rx_error"), using=const_nan))


        # add bitstream data objects
        for node in nodes:

            y = np.array([], dtype=[
                ("gts", np.float64),        # float to enable explicit visibility of clock drift
                ("rx_symbol", np.int8),
                ("rx_error", np.int8),
                ("schedule_gts", trx["schedule_gts"].dtype),
                ("destination_node_id", rx_info["destination_node_id"].dtype)
                ])

            # traverse receptions of something
            r = (x for x in trx_array if x['node_id'] == node and x['operation'] == 0 and 
                x['trx_status:header_detected'] and not x['trx_status:timeout'])
            for trx in r:

                # get corresponding rx_info
                rxi = [x for x in rxi_array if x['schedule_gts'] == trx['schedule_gts'] and x['destination_node_id'] == node]
                if not rxi:     # e.g. because schedule_gts == -1
                    continue
                assert(len(rxi) == 1)
                rxi = rxi[0]

                # get transmitter's TRX entry
                if rxi['source_node_id'] < 0:
                    trx_tx = None
                else:
                    x = [x for x in trx_array if x['schedule_gts'] == rxi['schedule_gts'] and x['node_id'] == rxi['source_node_id']]
                    assert(len(x) == 1)
                    trx_tx = x[0]

                # extract bitstreams
                # ATTENTION: bits include the CRC, which is transmitted MSB first (in contrast to the PDU bytes)
                # TODO: check if last 3 bytes (CRC) must be bit-reversed here
                if not trx_tx is None:
                    src_bits = np.unpackbits(np.frombuffer(base64.b16decode(trx_tx['packet_content_raw']), dtype=np.uint8), bitorder='little')
                dst_bits = np.unpackbits(np.frombuffer(base64.b16decode(trx['packet_content_raw']), dtype=np.uint8), bitorder='little')

                # compute timestamps
                # NOTE: packet_lts marks reception of address field
                # ATTENTION: subtracting schedule_lts early ensures correct datatype and wrap-around handling
                # (adding a standard Python integer can silently extend the bit width)
                if True:
                    header_bits     = np.full(8 + 32, 2, np.int8)   # preamble + access address, value 2 = unknown (only timing)
                    ts_pdu_begin    = trx['packet_lts'] - trx['schedule_lts']
                    ts_pdu_end      = trx['end_lts'] - trx['schedule_lts']
                    ts_header_begin = ts_pdu_begin - (len(header_bits) * (ts_pdu_end - ts_pdu_begin)) / len(dst_bits)
                    if not trx_tx is None:
                        bitshift = 0
                        if rxi['ambiguous_source'] != b'' and rxi['ambiguous_source'] in b'?!!':
                            ts_shift = np.int64(ts_pdu_begin) - np.int64(trx_tx['packet_lts'] - trx_tx['schedule_lts'])
                            bitshift = np.int32(np.rint(gts_ticks_to_us(ts_shift)))
                        # print(f"{rxi['schedule_gts']=}; {rxi['destination_node_id']=}; {rxi['source_node_id']=}; {rxi['ambiguous_source']=}; {bitshift=}")
                else:   # BLE modes != 1M
                    assert(False)
                    # TODO: CI, TERM1, TERM2 (in long range modes)
                    # ts_pdu_begin = (trx['packet_lts'] - trx['schedule_lts']) + CI / TERM1
                    # ts_pdu_end   = (trx['end_lts'] - trx['schedule_lts']) - TERM2
                ts_pdu_begin    += trx['schedule_gts']
                ts_pdu_end      += trx['schedule_gts']
                ts_header_begin += trx['schedule_gts']

                # assemble data
                # NOTE: two extra symbols with value -1 are used as packet boundary markers

                n = len(y)
                y.resize(n + 1 + len(header_bits) + len(dst_bits) + 1, refcheck=False)

                y['gts'][n+1:] = np.linspace(ts_header_begin, ts_pdu_end, len(header_bits) + len(dst_bits) + 1, endpoint=True, dtype=np.float64)
                # y['gts'][n+1:] = np.linspace(ts_pdu_begin, ts_pdu_end, len(dst_bits) + 1, endpoint=True, dtype=np.float64)
                ts = y['gts'][n+1:n+3]
                y['gts'][n] = ts[0] - (ts[1] - ts[0])

                n_header = n + 1
                n_pdu = n_header + len(header_bits)

                y['rx_symbol'][n_header : n_pdu] = header_bits
                y['rx_symbol'][n_pdu : -1] = dst_bits
                y['rx_symbol'][[n,-1]] = -1

                if trx_tx is None:
                    y['rx_error'][n:] = -1      # error information is unavailable
                else:
                    y['rx_error'][n_header : n_pdu] = -1
                    if bitshift < 0:
                        src_bits = np.concatenate((np.full(min(-bitshift, len(dst_bits)), 2, np.uint8), src_bits))
                    else:
                        src_bits = src_bits[bitshift:]
                    l1 = min(len(src_bits), len(dst_bits))
                    n1 = n_pdu + l1
                    y['rx_error'][n_pdu : n1] = (src_bits[:l1] != dst_bits[:l1])
                    y['rx_error'][n1:] = 1
                    y['rx_error'][[n,-1]] = -1

                y['schedule_gts'][n:] = rxi['schedule_gts']
                y['destination_node_id'][n:] = node

            data.append(Data(label=f"bitstream_{node}", **dict(map(lambda n: (n, y[n]), y.dtype.names))))
            x = data[-1]
            x.add_component_link(ComponentLink([x.id["schedule_gts"], x.id["destination_node_id"]], ComponentID("destination_node_key"), using=node_key))

            x.add_component_link(ComponentLink([x.id["gts"]], ComponentID("gts_us"), 
                using=gts_ticks_to_us, inverse=gts_us_to_ticks))
            x.add_component_link(ComponentLink([x.id["gts"]], ComponentID("gts_s"), 
                using=gts_ticks_to_s, inverse=gts_s_to_ticks))

            # add dummy components to establish "viewer compatibility" with RSSI data
            # NOTE: the source for const_nan() is a dummy, so any field can be used
            x.add_component_link(ComponentLink([x.id["schedule_gts"]], ComponentID("rssi_dBm"), using=const_nan))
            x.add_component_link(ComponentLink([x.id["schedule_gts"]], ComponentID("rssi_mW"), using=const_nan))


    return data

####################################################################################################
# custom TRX auto-linker
# for details, see
# <https://docs.glueviz.org/en/stable/customizing_guide/customization.html#custom-auto-linking-helper>

@autolinker(product_name + " TRX Auto-Linker")
def trx_autolinker(dc):
    
    global trx_loader_info
    # print(f"{trx_loader_info=}")

    toc = dict(zip(dc.labels, range(len(dc.labels))))

    # use "nodes" to test if file has been analyzed (-> trx_analyze.py)
    if "trx" not in toc or "nodes" not in toc:
        return []

    trx             = dc.data[toc["trx"]]
    nodes           = dc.data[toc["nodes"]]
    transactions    = dc.data[toc["transactions"]]
    rx_info         = dc.data[toc["rx_info"]]
    link_matrix     = dc.data[toc["link_matrix"]]
    rssi_data       = dc.data[toc["rssi_data"]]

    links = []

    # We implement a mixture of database-like joins and ComponentLinks.
    # Both of them have pros and cons:
    # * ComponentLink:
    #   + visible in glue's link manager
    #   + allows multiple links between two Data objects (e.g. source_node_id => node_id, destination_node_id => node_id)
    #   + explicit support for link functions
    #   - can be tricky in terms of selections (restricting selections to the meant components)
    # * database-like joins (established with Data.join_on_key()):
    #   - invisible in glue's link manager (glue 1.2.x)
    #   - at most one link between two Data objects (otherwise ambiguous)
    #   + "real" joins, i.e. robust with respect to selections (independent of the criteria defining a selection)
    # Essentially, ComponentLinks define how selections can be applied to different Data objects.
    # This means that the Data objects must provide all fields used in the selection.
    # In contrast, joins mark corresponding data entries (i.e. they define a strict relation between Data objects).
    # With their help selections can be mapped between Data objects based on corresponding entries.
    # In a sense, one can compare ComponentLinks with soft links and joins with hard links.

    # install database-like joins
    # ATTENTION: connections are made even if Auto-Linker is aborted in the GUI.
    # This is dirty, but what is a better way? We could make the joins directly on load
    # (join_on_key() does not depend on dc), but this does not change much.
    # NOTE: there are performance issues with multiple component links, see comments in TRX Loader
    nodes.join_on_key(trx, "node_id", "node_id")
    transactions.join_on_key(trx, "schedule_gts", "schedule_gts")
    rx_info.join_on_key(trx, "destination_node_key", "destination_node_key")
    # rx_info.join_on_key(trx, ["schedule_gts", "destination_node_id"], ["schedule_gts", "destination_node_id"])
    rssi_data.join_on_key(trx, "anchor", "rssi:data_anchor")
    for n in nodes["node_id"]:
        s = f"rssi_{n}"
        if s in dc.labels:
            dc.data[dc.labels.index(s)].join_on_key(trx, "destination_node_key", "destination_node_key")
        s = f"bitstream_{n}"
        if s in dc.labels:
            dc.data[dc.labels.index(s)].join_on_key(trx, "destination_node_key", "destination_node_key")

    # link (schedule_)gts and source/dest_node_id fields
    gts_anchor = None
    for x in dc.data:
        if x.label == "trx":
            continue
        # do not link empty datasets, this causes trouble (glue 1.2.4)
        if not x.size:
            continue
        from_id = x.find_component_id("gts")
        if from_id is not None:
            if gts_anchor is None:
                gts_anchor = x
            else:
                links.append(ComponentLink([from_id], gts_anchor.id["gts"]))    
        from_id = x.find_component_id("schedule_gts")
        if from_id is not None:
            links.append(ComponentLink([from_id], trx.id["schedule_gts"]))
        from_id = x.find_component_id("source_node_id")
        if from_id is not None:
            links.append(ComponentLink([from_id], trx.id["source_node_id"]))
        from_id = x.find_component_id("destination_node_id")
        if from_id is not None:
            links.append(ComponentLink([from_id], trx.id["destination_node_id"]))
        # from_id = x.find_component_id("node_id")
        # if from_id is not None:
        #     links.append(ComponentLink([from_id], trx.id["node_id"]))
        # gts_id = x.find_component_id("schedule_gts")
        # src_id = x.find_component_id("source_node_id")
        # dst_id = x.find_component_id("destination_node_id")
        # if gts_id is not None:
        #     if dst_id is not None:
        #         x.join_on_key(trx, ["schedule_gts", "destination_node_id"], ["schedule_gts", "destination_node_id"])
        #     elif src_id is not None:
        #         x.join_on_key(trx, ["schedule_gts", "source_node_id"], ["schedule_gts", "source_node_id"])

    # add specific links

    # destination_node_id link is available implicitly via joins rx_info -> trx -> nodes
    links.append(ComponentLink([rx_info.id["source_node_id"]], nodes.id["node_id"]))
    # links.append(ComponentLink([rx_info.id["destination_node_id"]], nodes.id["node_id"]))

    links.append(ComponentLink([link_matrix.components[0]], nodes.id["node_id"]))

    # link RSSI tables (important if user wants to use the same scatter plot instance)
    anchor = None
    for n in nodes["node_id"]:
        s = f"rssi_{n}"
        if s in dc.labels:
            x = dc.data[dc.labels.index(s)]
            if anchor is None:
                anchor = x
            else:
                links.append(ComponentLink([x.id['rssi_dBm']], anchor.id['rssi_dBm']))
                # NOTE: (schedule)_gts etc. has been linked above

    # link bitstream tables
    anchor = None
    for n in nodes["node_id"]:
        s = f"bitstream_{n}"
        if s in dc.labels:
            x = dc.data[dc.labels.index(s)]
            if anchor is None:
                anchor = x
            else:
                links.append(ComponentLink([x.id['rx_symbol']], anchor.id['rx_symbol']))
                links.append(ComponentLink([x.id['rx_error']], anchor.id['rx_error']))
                # NOTE: (schedule)_gts etc. has been linked above

    # link markers
    for m in trx_loader_info["markers"]:
        dest = trx_loader_info["markers"][m]
        sdata = dc.data[toc[m]]
        ddata = dc.data[toc[dest[0]]]
        # try join, use ComponentLink if join is to slow
        sdata.join_on_key(ddata, ["schedule_gts", "node_id"], ["schedule_gts", dest[1]])
        # links.append(ComponentLink([sdata.id["node_id"]], ddata.id[dest[1]]))
        # NOTE: schedule_gts has been linked above

    return links

####################################################################################################
# custom data viewer that shows RSSI together with bitstream and biterrors
# for details see https://docs.glueviz.org/en/stable/customizing_guide/custom_viewer.html
# ATTENTION: The following implementation relies on the matplotlib viewer framework provided by Glue.
# This framework is very easy to use, for the price of some limitations regarding flexibility.
# In consequence, the viewer is a (quick and really) dirty solution and contains some issues
# that should be solved by implementing a clean own viewer class.

rx_viewer = custom_viewer(product_name + " Rx Viewer",
                gts             = 'att(gts)',
                gts_us          = 'att(gts_us)',
                gts_s           = 'att(gts_s)',
                rssi            = 'att(rssi_dBm)',
                rssi_lin        = 'att(rssi_mW)',
                rx_symbol       = 'att(rx_symbol)',
                rx_error        = 'att(rx_error)',
                timestamp_unit  = ['Ticks', 'us', 's'],
                linear_rssi     = False
                #save_to_files   = ['', 'glue_plot.tikz']
                )

# def squeeze(x, y, xlim):
#     print(f'{xlim=}; {x.size=}; {x[0]=}; {x[-1]=}')
#     k = (np.searchsorted(x, xlim[0], side='left'), np.searchsorted(x, xlim[1], side='right'))
#     print(f'{k=}')
#     k = (max(0, k[0] - 1), min(x.size, k[1] + 1))
#     print(f'{k=}')
#     x = x[k[0]:k[1]]
#     y = y[k[0]:k[1]]
#     print(f'{x.size=}; {x[0]=}; {x[-1]=}')
#     xi = np.empty(x.size * 2)
#     yi = np.empty(x.size * 2)
#     dx = (x[-1] - x[0]) / 4000
#     i = 0
#     xi[i] = xi[i+1] = x[0]
#     yi[i] = yi[i+1] = y[0]
#     for k in range(x.size):
#         if (x[k] - xi[i]) >= dx:
#             i += 2
#             xi[i] = xi[i+1] = x[k]
#             yi[i] = yi[i+1] = y[k]
#         else:
#             yi[i] = min(yi[i], y[k])
#             yi[i+1] = max(yi[i+1], y[k])
#     return (xi[0:i+1].copy(), yi[0:i+1].copy())

# setup function (called once)
@rx_viewer.setup
def rx_viewer_setup(axes, state):

    # print(f'rx_viewer_setup {id(axes)=}')
    # print(f'{axes.figure=}')

    # store figure handle
    # this is done to have it for sure because we possibly decouple the axes object (see below)
    fig = axes.figure
    state.figure = fig

    # axes is created and partially managed (margins, callbacks, etc.) outside of this function.
    # Normally this is good, as it simplifies things. However, it introduces some difficulties
    # if multiple axes objects are needed. We work around that in a somewhat dirty way to save
    # the effort of implementing a full CustomViewer class (which would be more clean, of course).

    # create "our" axes objects
    # NOTE: 'axes' (the existing object) is not part of the constrained layout
    fig.set_constrained_layout(dict(hspace=0, wspace=0))
    fig.subplots(2, 1, sharex=True, gridspec_kw=dict(height_ratios=[1, 0.2]))
    ax1, ax2 = fig.axes[-2:]
    ax1.set_ylabel("RSSI")
    ax1.grid(visible=True)
    ax2.set_xlabel("gts")
    ax2.set_ylabel("bitstream")
    ax2.set_ylim((-0.1, 1.1))
    ax2.set_yticks([0, 1])
    ax2.grid(visible=True, axis='x')
    ax2.set_navigate(False)
    # ax1.autoscale(enable=True)
    # ax2.autoscale(enable=True)

    # two options for 'axes' (the existing object)
    if False:
        # 1) decouple it from the figure
        # This is possible if there is no need for (a) subset selection tools in the viewer
        # and (b) callbacks in case of pan, zoom, and the like.
        # Decoupling 'axes' is best for performance.
        fig.delaxes(axes)
    else:
        # 2) make it invisible
        # This allows to implement subset selection and keeps callbacks active.
        # ATTENTION: axes.set_visible(False) cannot be used to reach this goal.
        axes.set_frame_on(False)
        axes.set_axis_off()
        # to enable selections:
        # bring 'axes' to the front (selection tool works only inside 'axes')
        axes.set_zorder(ax2.get_zorder() + 1)
        # match 'axes' with the full figure
        # -> no restrictions for selections
        # -> simplifies calculations when transforming selections to "our" axes objects
        axes.resizer.margins = [0,0,0,0]
        # disable pan and zoom on 'axes'
        # this is important to avoid trouble with overlapped axes objects
        axes.set_navigate(False)


# main plot function
@rx_viewer.plot_data
def rx_viewer_plot_data(axes, state, style, gts, gts_us, gts_s, rssi, rssi_lin, timestamp_unit, linear_rssi, rx_symbol, rx_error):

    # print(f'rx_viewer_plot_data {id(axes)=}')
    # print(f'{axes.figure=}')
    # print(f'{gts.id=}; {gts=}\n{rssi=}')
    # print(f'{style=}\n{style.alpha=};{style.color=};{style.linestyle=};{style.linewidth=};{style.marker=};{style.markersize=};{style.preferred_cmap=};{style.rgba=}')

    state.gts_id = gts.id

    fig = state.figure
    ax1, ax2 = fig.axes[-2:]    # [0] can contain 'axes' (depending on what we do in rx_viewer_setup())
    ret = []

    if 'us' == timestamp_unit:
        gts = gts_us
        ax2.set_xlabel("global timestamp [us]")
        state.x_to_ticks = gts_us_to_ticks
    elif 's' == timestamp_unit:
        gts = gts_s
        ax2.set_xlabel("global timestamp [s]")
        state.x_to_ticks = gts_s_to_ticks
    else:
        ax2.set_xlabel("global timestamp [ticks]")
        state.x_to_ticks = lambda x: x

    # adapt xbound to current timescale
    x = 0.05 * (gts[-1] - gts[0])
    l = gts[0] - x
    u = gts[-1] + x
    ax1.set_xbound(lower=l, upper=u)
    ax2.set_xbound(lower=l, upper=u)

    # if dataset is a RSSI dataset
    if not np.isnan(rssi).all():

        y = rssi_lin if linear_rssi else rssi
        # x,y = squeeze(gts, y, ax1.get_xlim())
        # ret += ax1.plot(x, y, 
        ret += ax1.plot(gts, y, 
            alpha=style.alpha, color=style.color, linewidth=style.linewidth, linestyle=style.linestyle, 
            marker=style.marker, markersize=style.markersize
            )

        if linear_rssi:
            ax1.set_ybound(lower=0, upper=None)
            ax1.set_ylabel("RSSI [mW]")
        else:
            ax1.set_ybound(lower=-130, upper=130)
            ax1.set_ylabel("RSSI [dBm]")

    # if dataset is a bitstream dataset
    # if not np.isnan(rx_symbol).all():
    else:

        # plot rx_symbols
        y = np.float16(rx_symbol)
        y[rx_symbol < 0] = np.nan
        y[rx_symbol > 1] = 0.5
        y1 = y.copy()
        y[rx_error < 0] = np.nan    # save ones (with rx_error available)
        ret += ax2.step(gts, y, '-', where='post', 
            alpha=style.alpha, color=style.color, marker='|', markersize=7
            )
        y1[rx_error >= 0] = np.nan  # unsave ones (with rx_error unavailable)
        ret += ax2.step(gts, y1, ':', where='post', 
            alpha=style.alpha, color=style.color, marker='|', markersize=7
            )

        # plot rx_error as special markers on top of rx_symbols
        y = np.float16(rx_error)
        mask = (rx_error < 1)
        y[mask] = np.nan
        mask = ~mask
        y[mask] = rx_symbol[mask]
        ret += ax2.step(gts, y, where='post', 
            alpha=0.5, color='red', linewidth=5, 
            marker='o', markersize=style.markersize*4, mec='red', mfc=style.color #, mfcalt='red', fillstyle='top'
            )

    # return generated artists
    return ret


# subset markers plot function
@rx_viewer.plot_subset
def rx_viewer_plot_subset(axes, state, style, gts, gts_us, gts_s, rssi, rssi_lin, timestamp_unit, linear_rssi, rx_symbol, rx_error):

    fig = state.figure
    ax1, ax2 = fig.axes[-2:]
    ret = []

    gts = gts_us if timestamp_unit == 'us' else gts_s if timestamp_unit == 's' else gts

    # if dataset is a RSSI dataset
    if not np.isnan(rssi).all():

        y = rssi_lin if linear_rssi else rssi
        ret += ax1.plot(gts, y, 'o',
            alpha=style.alpha, mec=style.color, mfc=style.color, markersize=style.markersize
            )

    # if dataset is a bitstream dataset
    # if not np.isnan(rx_symbol).all():
    else:

        y = np.float16(rx_symbol)
        y[rx_symbol < 0] = np.nan
        y[rx_symbol > 1] = 0.5
        ret += ax2.plot(gts, y, 'o', 
            alpha=style.alpha, mec=style.color, mfc=style.color, markersize=style.markersize
            )

    return ret


# specific select implementation
# this function translates a RectangularROI (region of interest) into a SubsetState
@rx_viewer.make_selector
def rx_viewer_make_selector(state, roi):

    # print(f'{state=}\n{roi=}\n{roi}')

    # get coordinates and limits of x-axis (gts)
    ax2 = state.figure.axes[-1]
    rel = ax2.get_position()
    xmin, xmax = ax2.get_xlim()

    # restrict selection to the axis
    roi_min = max(rel.xmin, min(rel.xmax, roi.xmin))
    roi_max = max(rel.xmin, min(rel.xmax, roi.xmax))

    # transform roi coordinates into gts bounds
    mul = (xmax - xmin) / (rel.xmax - rel.xmin)
    xlo = xmin + ((roi_min - rel.xmin) * mul)
    xhi = xmin + ((roi_max - rel.xmin) * mul)

    xlo = state.x_to_ticks(xlo)
    xhi = state.x_to_ticks(xhi)

    # print(f'{xlo=}; {xhi=}')

    # return selection as SubsetState
    return RangeSubsetState(xlo, xhi, state.gts_id)


## specific select implementation
## this function translates a RectangularROI (region of interest) to a boolean mask
#@rx_viewer.select
#def rx_viewer_select(state, roi, gts):
#
#    # ... (as in rx_viewer_make_selector())
#
#    # return selection as boolean mask
#    return (gts >= xlo) & (gts <= xhi)

####################################################################################################
