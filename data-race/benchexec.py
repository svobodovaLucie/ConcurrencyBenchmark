import os
from termcolor import colored

folder_path = "."
true_count = 0
false_count = 0

# Get list of filenames and sort them by their name
filenames = sorted(os.listdir(folder_path))

# Analyze the files
for filename in filenames:
    if filename.endswith(".c"):
        command = f"sudo infer --darc-only -- gcc -c {filename} 2> /dev/null | grep 'Found \\|No issues found'"
        output = os.popen(command).read().strip()
        if "_data-race.c" in filename:
            # Check for data races
            if "Found " in output:
                result = colored("passed", "green")
                true_count += 1
            elif "No issues found" in output:
                result = colored("failed", "red")
                false_count += 1
            else:
                result = "unknown"
        elif "_no-data-race.c" in filename:
            # Check for no data races
            if "Found " in output:
                result = colored("failed", "red")
                false_count += 1
            elif "No issues found" in output:
                result = colored("passed", "green")
                true_count += 1
            else:
                result = "unknown"
        else:
            result = output
        print(f"{filename}: {result}")

# Remove all *.o files
os.system(f"rm -rf {folder_path}/*.o")

if true_count > 0:
	print(f"\nPassed tests: {colored(true_count, 'green')}")
else:
	print(f"Passed tests: {true_count}")

if false_count > 0:
	print(f"Failed tests: {colored(false_count, 'red')}")
else:
	print(f"Failed tests: {false_count}")
