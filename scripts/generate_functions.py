import os
import re

# Directory path where your .hpp files are located
src_dir = 'src/'

# List to store function names
functions = []

# Regular expression to match function declarations
function_pattern = re.compile(r'\w+\s+\w+\s*\([^)]*\)\s*;')

# Iterate through files in the directory
for filename in os.listdir(src_dir):
    if filename.endswith('.hpp'):
        file_path = os.path.join(src_dir, filename)
        with open(file_path, 'r') as file:
            content = file.read()
            # Find all function declarations using regex
            matches = function_pattern.findall(content)
            # Extract function names from matches
            for match in matches:
                # Remove any unnecessary whitespace and semicolons
                function_name = match.split('(')[0].strip()
                functions.append(function_name)

# Generate Markdown content
markdown_content = "## Functions in .hpp files under 'src':\n\n"
markdown_content += "```\n"
for func in functions:
    markdown_content += func + "\n"
markdown_content += "```\n"

# Write to a Markdown file
markdown_file_path = 'bin/mdpyscript.md'
with open(markdown_file_path, 'w') as markdown_file:
    markdown_file.write(markdown_content)

print(f"Function list generated in {markdown_file_path}")
