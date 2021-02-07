"""
input   '1 + 2 - 3'
return  0
"""

def getOperator(s, cur):
    return s[cur], cur + 1

def getNumber(s, cur):
    ret = ''
    if s[cur] == "-":
        ret, cur= '-', cur + 1
    while cur < len(s) and s[cur].isdigit():
        ret, cur = ret + s[cur], cur + 1
    return int(ret), cur

def foo(s):
    s = s.replace(" ", "")
    if s[0].isdigit():
        s = "+" + s
    stack = []
    cur = 0
    while cur < len(s):
        op, cur = getOperator(s, cur)
        num, cur = getNumber(s, cur)
        if op == "*":
            stack[-1] *= num
        elif op == "+":
            stack.append(num)
        else:
            stack.append(-num)
    return str(sum(stack))

def extend(s):
    start= -1
    for idx, c in enumerate(s):
        if c == "(":
            start = idx
        elif c == ")":
            end = idx
            subres = foo(s[start+1:end])
            s = s[:start] + subres + s[end+1:]
            return extend(s)
    
    return foo(s)

# print(extend('(1 + 2) - 4'))
# print(extend('1 + 2 - 4'))
print(extend(' 1 - 2 '))
print(extend('(3 - 3) * ( 1 - 2 )'))

    