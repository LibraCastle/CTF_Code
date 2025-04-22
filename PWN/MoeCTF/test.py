print("Please input the expression you want to calculate:")
input_str = input()
print(f"The result is : {eval(input_str)}")

hex_bytes = bytes.fromhex(
    "e4bda0e8bfe7e585b3e380820a6d6f656374667b40723154484d657469435f69735f4e30545f4d345468334d4074696353316263633234317d0a0a"
)

print(hex_bytes.decode(errors="ignore"))
 