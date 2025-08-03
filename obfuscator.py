#!/usr/bin/env python3
import re
import random
import string
import os

def generate_random_string(length=8):
    """Generate a random string for obfuscation"""
    return ''.join(random.choices(string.ascii_letters, k=length))

def obfuscate_string(s):
    """Obfuscate a string by converting to hex and XOR"""
    if not s or len(s) == 0:
        return '""'
    
    # Generate a random XOR key
    xor_key = random.randint(1, 255)
    
    # Convert string to hex and XOR
    hex_chars = []
    for char in s:
        hex_val = ord(char) ^ xor_key
        hex_chars.append(f"0x{hex_val:02x}")
    
    # Create deobfuscation function
    func_name = f"deobf_{generate_random_string(6)}"
    deobf_code = f"""
inline std::string {func_name}() {{
    const unsigned char data[] = {{{', '.join(hex_chars)}}};
    const int key = {xor_key};
    std::string result;
    for (int i = 0; i < {len(hex_chars)}; i++) {{
        result += static_cast<char>(data[i] ^ key);
    }}
    return result;
}}"""
    
    return f"{func_name}()", deobf_code

def obfuscate_file(file_path):
    """Obfuscate strings in a C++ file"""
    print(f"Obfuscating: {file_path}")
    
    with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
        content = f.read()
    
    # Find all string literals
    string_pattern = r'"([^"\\]*(?:\\.[^"\\]*)*)"'
    strings = re.findall(string_pattern, content)
    
    # Filter out strings that shouldn't be obfuscated (like file paths, includes, etc.)
    skip_patterns = [
        r'^#',  # Preprocessor directives
        r'^\.',  # File extensions
        r'^[A-Za-z_][A-Za-z0-9_]*$',  # Single identifiers
        r'^[0-9]+$',  # Numbers
        r'^[A-Za-z0-9_]+\.(h|cpp|hpp)$',  # File names
        r'^[A-Za-z0-9_]+\.(exe|dll|pdb)$',  # Executable names
        r'^[A-Za-z0-9_]+\.(ttf|otf)$',  # Font files
        r'^[A-Za-z0-9_]+\.(json|ini)$',  # Config files
    ]
    
    filtered_strings = []
    for s in strings:
        should_skip = False
        for pattern in skip_patterns:
            if re.match(pattern, s):
                should_skip = True
                break
        if not should_skip and len(s) > 2:  # Skip very short strings
            filtered_strings.append(s)
    
    # Remove duplicates
    filtered_strings = list(set(filtered_strings))
    
    # Generate obfuscated versions
    obfuscated_content = content
    deobf_functions = []
    
    for s in filtered_strings:
        if s in obfuscated_content:
            obfuscated_str, deobf_func = obfuscate_string(s)
            deobf_functions.append(deobf_func)
            obfuscated_content = obfuscated_content.replace(f'"{s}"', obfuscated_str)
    
    # Add deobfuscation functions at the top of the file
    if deobf_functions:
        # Find the first #include or #pragma
        lines = obfuscated_content.split('\n')
        insert_pos = 0
        for i, line in enumerate(lines):
            if line.strip().startswith('#include') or line.strip().startswith('#pragma'):
                insert_pos = i + 1
        
        # Insert deobfuscation functions
        deobf_code = '\n'.join(deobf_functions)
        lines.insert(insert_pos, deobf_code)
        obfuscated_content = '\n'.join(lines)
    
    # Write obfuscated content
    backup_path = file_path + '.backup'
    with open(backup_path, 'w', encoding='utf-8') as f:
        f.write(content)
    
    with open(file_path, 'w', encoding='utf-8') as f:
        f.write(obfuscated_content)
    
    print(f"Obfuscated {len(filtered_strings)} strings in {file_path}")
    print(f"Backup saved to {backup_path}")

def main():
    """Main function to obfuscate all C++ files"""
    cpp_files = [
        'main.cpp',
        'options.h',
        'globals.h',
        'Renderer/renderer.h',
        'Hacks/esp.h',
        'Hacks/parry.h',
        'Hacks/misc.h',
        'Utils/configs.h',
        'Caches/playercache.h',
        'Caches/playerobjectscache.h',
        'Caches/TPHandler.h',
        'Memory/MemoryManager.h',
        'SDK/sdk.h',
        'Renderer/W2S.h'
    ]
    
    for file_path in cpp_files:
        if os.path.exists(file_path):
            try:
                obfuscate_file(file_path)
            except Exception as e:
                print(f"Error obfuscating {file_path}: {e}")
        else:
            print(f"File not found: {file_path}")

if __name__ == "__main__":
    main()