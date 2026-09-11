def papers_needed1(reader):
    res = 0
    while True:
        line = reader.readline()

        if not line:
            break

        temp = 0
        val = [0] * 3

        i = 0
        for ch in line:
            if ch == '\n':
                val[2] = temp
            elif ch != 'x':
                temp = temp * 10 + int(ch)
            else:
                val[i] = temp
                temp = 0
                i += 1

        val[2] = temp
        length = val[0] * val[1]
        width  = val[1] * val[2]
        height = val[2] * val[0]
        temp   = min(length, width, height)
        length *= 2
        width  *= 2
        height *= 2
        res    += length + width + height

    return res

def papers_needed2(reader):
    res = 0
    while True:
        line = reader.readline()

        if not line:
            break

        temp = 0
        val = [0] * 3

        i = 0
        for ch in line:

            if ch == '\n':
                val[2] = temp
            elif ch != 'x':
                temp = temp * 10 + int(ch)
            else:
                val[i] = temp
                temp = 0
                i += 1

        val[2] = temp
        temp = val[0] * val[1] * val[2]
        let_max = max(val)
        i = 0
        k = 0

        while i < 3:
            if let_max == val[i] and k == 0:
                k += 1
                i += 1
                continue

            res += val[i] + val[i]
            i += 1

        res += temp

    return res

def get_file_size(reader):
    reader.seek(0, 2)
    size = reader.tell()
    return size

def main():
    with open("../inputs/2015day2.txt",'r') as reader:
        size = get_file_size(reader)
        reader.seek(0, 0)
        result1 = papers_needed1(reader)
        reader.seek(0, 0)
        result2 = papers_needed2(reader)
        print("part 1 result", result1)
        print("part 2 result", result2)
    return

if __name__ == "__main__":
    main()
