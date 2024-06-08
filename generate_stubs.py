import re

def generate_stub_function(return_type, function_name):
    # Generate the stub function with the body commented out
    stub = f"{return_type} {function_name}(void) {{\n"
    stub += "    // STUB\n"
    if return_type != "void":
        stub += f"    return ({return_type})0;  // Default return value\n"
    stub += "}\n\n"
    return stub

def rename_original_function(file_content, function_name, return_type):
    # Replace the original function name in the definition with a new name
    new_function_name = function_name + "_original"
    pattern = rf"\b({return_type})\s+({function_name})\b(?=\s*\()"
    renamed_content = re.sub(pattern, rf"\1 {new_function_name}", file_content)
    return renamed_content

def insert_stub_function(file_content, stub_function):
    # Insert the stub function after the last #include directive
    lines = file_content.split('\n')
    insert_index = 0
    for i, line in enumerate(lines):
        if line.startswith('#include'):
            insert_index = i + 1
    lines.insert(insert_index + 1, stub_function)
    return '\n'.join(lines)

def main():
    # Hardcoded arguments
    file_location = "edk2/MdeModulePkg/Core/PiSmmCore/SmramProfileRecord.c"
    return_type = "UINTN"
    function_name = "SmramProfileGetDataSize"
   
     # Read the file content
    with open(file_location, 'r') as f:
        file_content = f.read()

    # Rename the original function
    file_content = rename_original_function(file_content, function_name, return_type)

     # Generate the stub function
    stub = generate_stub_function(return_type, function_name)

    # Insert the stub function after the last #include directive
    file_content = insert_stub_function(file_content, stub)

    # Write the modified content back to the file
    with open(file_location, 'w') as f:
        f.write(file_content)

    print(f"Original '{function_name}' function renamed to '{function_name}_original' and stub function added to {file_location}")

if __name__ == "__main__":
    main()
