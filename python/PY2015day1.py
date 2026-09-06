def calculate_floor_p1(reader, size):

    floor = 0
    i = 0

    while i < size:
        chr = reader.read(1)

        if chr == b'\n':
            i += 1
            continue

        if chr == b'(':
            floor += 1
        else:
            floor -= 1

        i += 1

    return floor

def calculate_floor_p2(reader, size):

    floor = 0
    i = 0

    while i < size:
        chr = reader.read(1)

        if floor == -1:
            return i

        if chr == b'\n':
            i += 1
            continue

        if chr == b'(':
            floor += 1
        else:
            floor -= 1

        i += 1

    return floor

def size_of_file(file):
    file.seek(0, 2)
    size = file.tell()
    return size

def main():
    with open("../inputs/2015day1.txt", 'rb') as reader:
        size = size_of_file(reader)
        reader.seek(0, 0)
        result1 = calculate_floor_p1(reader, size);
        reader.seek(0, 0)
        result2 = calculate_floor_p2(reader, size);
        print("Floor :", result1)
        print("Floor :", result2)

    return;

main()
