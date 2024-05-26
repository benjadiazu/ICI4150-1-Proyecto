from json_ import read_json

if __name__=="__main__":
    data = read_json("files/test.json")

    for d in data:
        print("-------------")
        print(d)