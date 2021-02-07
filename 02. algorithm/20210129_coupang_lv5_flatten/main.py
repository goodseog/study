'''
압축률 4, 오차율 1.8 이하의 수열을 구하기
'''


def decomp(zarr):
    arr = []
    for cnt, val in zarr:
        arr += [val] * cnt
    return arr


def eval(arr1, zarr):
    arr2 = decomp(zarr)
    err = 0
    cnt = len(arr1)
    for i in range(cnt):
        err += (arr1[i] - arr2[i])**2
    err = (err / cnt) ** 0.5

    return len(arr1) / (len(zarr) * 2), err


def foo(arr):
    ans = []
    for val in arr:
        ans.append((1, val))

    while not (eval(arr, ans)[0] >= 4 and eval(arr, ans)[1] <= 1.8):
        best = (-1, 10000000000)
        for idx, pairs in enumerate(zip(ans[:-1], ans[1:])):
            p0, p1 = pairs
            arr1 = p0[0]*[p0[1]] + p1[0]*[p1[1]]
            arr2 = [(p0[0] + p1[0], (p0[0] * p0[1] + p1[0] * p1[1]) / (p0[0] + p1[0]))]
            _, score = eval(arr1, arr2)

            if best[1] > score:
                best = (idx, score)

        mergeIdx = best[0]
        p0, p1 = ans[mergeIdx], ans[mergeIdx + 1]
        res = (p0[0] + p1[0], (p0[0] * p0[1] + p1[0] * p1[1]) / (p0[0] + p1[0]))
        print(f"zip on idx #{mergeIdx}, {p0} and {p1}, as {res}")
        ans.pop(mergeIdx+1)
        ans[mergeIdx] = res
        

    return ans


arr = [
    35, 38, 36, 38, 37, 41, 40, 37, 40, 37, 37, 36, 40, 38, 35, 36, 37, 41, 35, 41,
    35, 35, 41, 36, 39, 39, 39, 36, 39, 41, 38, 38, 35, 40, 41, 35, 36, 41, 38, 39,
    36, 35, 28, 30, 27, 33, 29, 31, 30, 30, 30, 32, 31, 27, 28, 31, 33, 28, 33, 28,
    27, 27, 31, 29, 27, 30, 29, 31, 27, 31, 28, 29, 30, 31, 30, 30, 28, 28, 32, 33,
    30, 30, 32, 33, 32, 28, 28, 30, 30, 31, 32, 33, 33, 27, 28, 33, 29, 31, 30, 33,
    31, 30, 3, -2, 90, 89, 92, 91, 91, 89, 88, 88, 87, 88, 88, 89, 87, 93, 88, 93, 93, 91, 90, 90, 89, 91, 93, 91
]

print(foo(arr))
print(eval(arr, foo(arr)))
