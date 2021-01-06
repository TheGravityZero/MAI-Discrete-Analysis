import sys
import random
import string

TEST_COUNT = 8

def get_random_string():
    length = random.randint(1, 3)
    for _ in range(length):
         random_country = random_country + random.choice(string.digits)
    for _ in range(3):
        random_city =  random_city + random.choice(string.digits)
    for _ in range(7): 
        random_number = random_number + random.choice(string.digits) 
    random_list = "+" + random_country+"-"+random_city+"-"+random_number
    return "".join(random_list)

def get_random_value():   
    value = random(0,2**64-1)
    return value

def main():
    for _ in range(10):
        n = get_random_string()
        print(n)
"""    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} <test directory>")
        sys.exit(1)

    test_dir = sys.argv[1]

    lines = [0]
    lines.extend([ 10 ** i for i in range(TEST_COUNT) ])

    for enum, test_count in enumerate(range(1, TEST_COUNT+1)):
        test = []
        answer = []

        line_count = lines[enum]
        for _ in range(line_count):
            key = random.randint(1, 10_000)
            value = get_random_string()
            test.append((key, value))

        test_name = "{}/{:02d}".format(test_dir, test_count)
        with open(f'{test_name}.t', 'w') as ftest:
            for key, value in test:
                ftest.write(f'{key} {value}\n')

        answer = sorted(test, key=lambda x: x[0])
        with open(f'{test_name}.a', 'w') as ftest:
            for key, value in answer:
                ftest.write(f'{key} {value}\n')"""

if __name__ == '__main__':
    main()