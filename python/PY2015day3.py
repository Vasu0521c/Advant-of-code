def get_size(reader):
    reader.seek(0, 2)
    size = reader.tell()
    reader.seek(0, 0)
    return size

def gift_calculator1(reader):
    let_dict = dict()
    content  = reader.read()
    result   = 0
    i = j = 0
    for ch in content:
        match ch:
            case '^':
                i -= 1
                if (i, j) not in let_dict:
                    let_dict[(i,j)] = 0
                if let_dict[(i,j)] == 0:
                    result += 1
                let_dict[(i,j)] = 1
            case '<':
                j -= 1
                if (i, j) not in let_dict:
                    let_dict[(i,j)] = 0
                if let_dict[(i,j)] == 0:
                    result += 1
                let_dict[(i,j)] = 1
            case '>':
                j += 1
                if (i, j) not in let_dict:
                    let_dict[(i,j)] = 0
                if let_dict[(i,j)] == 0:
                    result += 1
                let_dict[(i,j)] = 1
            case 'v':
                i += 1
                if (i, j) not in let_dict:
                    let_dict[(i,j)] = 0
                if let_dict[(i,j)] == 0:
                    result += 1
                let_dict[(i,j)] = 1

    return result

def gift_calculator2(reader):
    let_dict = dict()
    content = reader.read()
    result = 0
    i = j = 0
    s = [0, 0]
    f = [0, 0]
    iv = 0
    for ch in content:
        if iv == 0:
            i = s[0]
            j = s[1]
        else:
            i = f[0]
            j = f[1]
        match ch:
            case '^':
                i -= 1
                if (i, j) not in let_dict:
                    let_dict[(i,j)] = 0
                if let_dict[(i,j)] == 0:
                    result += 1
                let_dict[(i,j)] = 1
                if iv == 0:
                    iv = 1
                    s[0] = i
                    s[1] = j
                else:
                    iv = 0
                    f[0] = i
                    f[1] = j
            case '<':
                j -= 1
                if (i, j) not in let_dict:
                    let_dict[(i,j)] = 0
                if let_dict[(i,j)] == 0:
                    result += 1
                let_dict[(i,j)] = 1
                if iv == 0:
                    iv = 1
                    s[0] = i
                    s[1] = j
                else:
                    iv = 0
                    f[0] = i
                    f[1] = j
            case '>':
                j += 1
                if (i, j) not in let_dict:
                    let_dict[(i,j)] = 0
                if let_dict[(i,j)] == 0:
                    result += 1
                let_dict[(i,j)] = 1
                if iv == 0:
                    iv = 1
                    s[0] = i
                    s[1] = j
                else:
                    iv = 0
                    f[0] = i
                    f[1] = j
            case 'v':
                i += 1
                if (i, j) not in let_dict:
                    let_dict[(i,j)] = 0
                if let_dict[(i,j)] == 0:
                    result += 1
                let_dict[(i,j)] = 1
                if iv == 0:
                    iv = 1
                    s[0] = i
                    s[1] = j
                else:
                    iv = 0
                    f[0] = i
                    f[1] = j
    return result
                
def main():
    with open("../inputs/2015day3.txt", 'r') as reader:
        size = get_size(reader)
        reader.seek(0, 0)
        result1 = gift_calculator1(reader)
        reader.seek(0, 0)
        result2 = gift_calculator2(reader)
        print("Part 1 : ",result1)
        print("Part 2 : ",result2)

if __name__ == "__main__":
    main()
    
