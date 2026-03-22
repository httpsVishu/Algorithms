import pandas as pd

# -------- CONFIGURATION SECTION --------

files = {
    "Bubble": "bubble_results.csv",
    "Insertion": "insertion_results.csv",
    "Selection": "selection_results.csv",
    "Merge": "merge_results.csv",
    "Heap": "heap_results.csv",
    "Quick": "quick_results.csv"
}

# Column you want to extract (change later if needed)
column_to_extract = "Comparisons"

output_file = "compiled_side_by_sides.csv"

# ---------------------------------------


# Read first file completely
first_algo = list(files.keys())[0]
base_df = pd.read_csv(files[first_algo])

# Keep common columns
final_df = base_df[["Array_No", "Type", "Size"]].copy()

# Add first algorithm comparison column
final_df[first_algo] = base_df[column_to_extract]

# Process remaining files
for algo in list(files.keys())[1:]:
    df = pd.read_csv(files[algo])
    final_df[algo] = df[column_to_extract]

# Save new CSV
final_df.to_csv(output_file, index=False)

print("Compiled CSV created successfully:", output_file)