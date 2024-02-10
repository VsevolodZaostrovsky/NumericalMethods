Здесь мы проверяем, что 
\begin{equation}
    \psi_k^{(n)} = \sin(\frac{\pi n k}{N})
\end{equation}    
решает систему
\begin{align*}
& -\frac{y_{k+1} - 2 y_k + y_{k-1}}{h^2} + p y_k = f_k, \;\;\;\;\; k = 1, \ldots, N - 1; \\
& y_0 = y_N = 0; \\
& h = \frac{1}{N}; \\
& p \geq 0.
\end{align*}
реализуйте метод Фурье (т.е. метод разложения по собственным векторам) для базисных функций:

