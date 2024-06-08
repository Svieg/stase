def find_and_copy_lines(input_file, output_file, keyword):
    # Open the input file in read mode and the output file in write mode
    with open(input_file, 'r') as infile, open(output_file, 'w') as outfile:
        # Iterate through each line in the input file
        for line in infile:
            # Check if the keyword is present in the current line
            if keyword in line:
                # If the keyword is found, write the whole line to the output file
                outfile.write(line)

# Specify the path to the input file
input_file = 'input.txt'
# Specify the path to the output file
output_file = 'output.txt'
# Specify the keyword or text to search for
keyword = 'search_phrase'

# Call the function with the specified parameters
find_and_copy_lines(input_file, output_file, keyword)
