import pandas

df = pandas.read_json('http://jonghank.github.io/ee370/files/speeches.json')

print(f"parties: {df['parties'][0]}")
print(f"speeches: {df['speeches'][0]}")
print("\n")
print(f"parties: {df['parties'][1]}")
print(f"speeches: {df['speeches'][1]}")
