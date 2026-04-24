def build_suffix_array(text):
	# Naive O(n^2 log n) suffix-array construction using suffix sorting.
	return sorted(range(len(text)), key=lambda i: text[i:])


T = "GATAGACA"
terminated = T + "$"

suffix_array = build_suffix_array(terminated)

print(f"Original string: {T}")
print(f"String used for suffix array: {terminated}")
print(f"Suffix array indices: {suffix_array}")

print("\nSorted suffixes:")
for idx in suffix_array:
	print(f"{idx}: {terminated[idx:]}")

