# import sys
# def recur(nums):
#     if not nums:
#         return 0
#     current = nums[0]**2 if nums[0] >= 0 else 0
#     return current + recur(nums[1:])

# def process_test_cases(test_cases):
#     if not test_cases:
#         return []
    
#     nums = list(map(int, test_cases[1].split()))
#     total_sum = recur(nums) 
    
#     return [total_sum] + process_test_cases(test_cases[2:])

# def main():
#     input_data = sys.stdin.read().strip().split("\n")
#     test_cases = input_data[1:]    
#     results = process_test_cases(test_cases)
        
#     def print_results(results, index=0):
#         if index >= len(results):
#             return
#         if index > 0:
#             print() 
#         print(results[index], end='')
#         print_results(results, index + 1)
    
#     print_results(results)


# if __name__ == "__main__":
#     main()


# {
#   "github_url": "https://gist.github.com/talib-sid/ec17462dda30ccfa467027839308ff4b",
#   "contact_email": "talib.siddiqui@students.iiit.ac.in",
#   "solution_language": "python"
# }


import pyotp
import hashlib
import time
import base64

key = b'talib.siddiqui@students.iiit.ac.inHENNGECHALLENGE003' 
hash_func = hashlib.sha512
time_step = 30
t0 = 0

def generate_totp(key, time_step, t0, hash_func):
    counter = int(time.time()) // time_step
    base32_key = base64.b32encode(key).decode('utf-8')
    totp = pyotp.TOTP(base32_key, interval=time_step, digest=hash_func)

    
    return totp.at(counter)

totp_code = generate_totp(key, time_step, t0, hash_func)
print("Generated TOTP:", totp_code)
