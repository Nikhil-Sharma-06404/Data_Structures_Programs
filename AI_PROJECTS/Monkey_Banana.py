def monkey_banana():
    t = int(input("Enter number of test cases: "))
    for case in range(1, t + 1):
        n = int(input(f"\nEnter height of diamond (upper triangle rows) for test case {case}: "))
        arr = []

        print("Enter the values row by row:")

        # Input upper triangle
        for i in range(n):
            row = list(map(int, input().split()))
            arr.append(row)

        # Input lower triangle
        for i in range(n - 1):
            row = list(map(int, input().split()))
            arr.append(row)

        dp = [[0] * n for _ in range(2 * n - 1)]
        dp[0][0] = arr[0][0]

        # Upper triangle DP
        for i in range(1, n):
            for j in range(i + 1):
                if j == 0:
                    dp[i][j] = dp[i - 1][j] + arr[i][j]
                elif j == i:
                    dp[i][j] = dp[i - 1][j - 1] + arr[i][j]
                else:
                    dp[i][j] = max(dp[i - 1][j - 1], dp[i - 1][j]) + arr[i][j]

        # Lower triangle DP
        for i in range(n, 2 * n - 1):
            for j in range(len(arr[i])):
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j + 1]) + arr[i][j]

        print(f"\nMaximum bananas collected in test case {case}: {dp[2 * n - 2][0]}")

# Run the function
monkey_banana()
