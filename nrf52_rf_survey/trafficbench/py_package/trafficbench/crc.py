"""
CRC computation function

polynomial: x^24 + x^10 + x^9 + x^6 + x^4 + x^3 + x + 1

TODO: test which variant is faster (should be crcmod, at least with C extension)
"""
try:
    # <https://pypi.org/project/crcmod>
    # <http://crcmod.sourceforge.net>
    import crcmod

    crc_core_function = crcmod.mkCrcFun(0b1000000000000011001011011, 0xAAAAAA, True, 0)

    def bitswap(num: int) -> int:
        return (num * 0x02_0202_0202 & 0x0108_8442_2010) % 1023

    bitswap_lut = bytes.maketrans(
        bytes(range(0, 256)), bytes(bitswap(x) for x in range(0, 256))
    )

    def calc_crc(data: bytes) -> bytes:
        return crc_core_function(data).to_bytes(3, "big").translate(bitswap_lut)

except BaseException:
    # <https://pypi.org/project/crc>
    from crc import Calculator
    from crc import Configuration

    crc_config = Configuration(
        width=24, polynomial=0b11001011011, init_value=0x555555, reverse_input=True
    )
    crc_calculator = Calculator(
        crc_config,
        optimized=True,
    )

    def calc_crc(data: bytes) -> bytes:
        return crc_calculator.checksum(data).to_bytes(3, "little")
