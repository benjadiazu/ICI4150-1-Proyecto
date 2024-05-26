import json

def read_json(path: str = None):
    if path is None: raise ValueError('Path is not valid')
    with open(path, 'r') as file:
        data = json.load(file)

    return data

def write_json(data = None, filename : str = None):
    if data is None or filename is None:
        raise ValueError('Data or Filename is None or both')
    
    with open(filename, 'w') as file:
        json.dump(data, file, indent=4)

    return True
