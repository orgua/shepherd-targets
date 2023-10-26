from enum import Enum


class ByteOrder(str, Enum):
    be = "be"
    big_endian = "be"
    le = "le"
    little_endian = "le"


def fletcher32(data: bytes) -> int:
    """compute Fletcher-32 checksum
    :param data:
    :return:
    """
    if not isinstance(data, bytes) or (len(data) & 1):
        raise AssertionError()

    len1_ = len(data)
    idx = 0
    c0 = c1 = 0

    while idx < len1_:
        len2_ = min(len1_ - idx, 360)

        for _ in range(len2_ // 2):
            c0 += (data[idx] << 8) | data[idx + 1]
            c1 += c0
            idx += 2

        c0 %= 0xFFFF
        c1 %= 0xFFFF

    return (c1 << 16) | c0


def test_checksum(
    data: bytes, position: list, byteorder: ByteOrder.big_endian, min_length: int
) -> None:
    """raises exception on mismatch

    :param data:
    :param position:
    :param byteorder:
    :param min_length:
    :return:
    """
    if len(data) < min_length:
        raise ValueError("invalid data length, checksum position out of range")
    if len(data) % 2:
        raise ValueError("invalid data length, should be even")
        # for fletcher32 as currently used/implemented

    c1 = data[position[0] : position[1]]
    if byteorder == "be":
        c1 = (c1[0] << 24) | (c1[1] << 16) | (c1[2] << 8) | (c1[3] << 0)
    elif byteorder == "le":
        c1 = (c1[0] << 0) | (c1[1] << 8) | (c1[2] << 16) | (c1[3] << 24)
    else:
        raise AssertionError()

    c2 = fletcher32(data[: position[0]])

    if c1 != c2:
        raise ValueError(f"checksum mismatch: {c1:#010x} != {c2:#010x}")
