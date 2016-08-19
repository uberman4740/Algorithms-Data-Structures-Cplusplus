bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    if(sr < 0 || sr > 9 || sc < 0 || sc > 9 || er < 0 || er > 9 ||
       ec < 0 || ec > 9 || maze[sr][sc] == 'X' || maze[er][ec] == 'X')
        return false;

    maze[sr][sc] = 'V';

    if(sr == er && sc == ec)
        return true;
    else if(maze[sr-1][sc] == '.' && pathExists(maze, sr-1, sc, er, ec))
        return true;
    else if(maze[sr][sc+1] == '.' && pathExists(maze, sr, sc+1, er, ec))
        return true;
    else if(maze[sr+1][sc] == '.' && pathExists(maze, sr+1, sc, er, ec))
        return true;
    else if(maze[sr][sc-1] == '.' && pathExists(maze, sr, sc-1, er, ec))
        return true;

    return false;
}