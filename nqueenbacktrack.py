def nqueen(n):
    board=[["."]*n for i in range(n)]
    # res=[]
    col=set()
    positiveDiag=set()
    negativeDiag=set()
    def backtrack(r):
        if(r==n):
            for i in board:
                print(i)
            print()
            return
        for c in range(n):
            if(c in col or (r-c) in negativeDiag or (r+c) in positiveDiag):
                continue
            col.add(c)
            positiveDiag.add(r+c)
            negativeDiag.add(r-c)
            board[r][c]="Q"
            backtrack(r+1)
            col.remove(c)
            positiveDiag.remove(r+c)
            negativeDiag.remove(r-c)
            board[r][c]="."
    backtrack(0)
nqueen(4)
