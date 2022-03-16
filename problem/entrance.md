# 迷宮入口 (entrance)

## 問題描述

勇者林克要找尋傳說中的寶劍。
寶劍被封印在地下迷宮的深處，而要進入地下迷宮，必須在特定的地方詠唱咒文。
迷宮的入口附近有 $`n`$ 個圖騰，詠唱咒文產生的聲波必須恰好傳遞至「奇數」個圖騰，迷宮的入口才能開啟。
以二維座標平面來看，已知圖騰位置在格子點 $`P_1, P_2, \ldots, P_n`$ 上，且詠唱咒文能傳遞的範圍為一半徑為 $`r`$ 的圓（包含圓周），請計算座標平面上有幾個格子點在其上詠唱咒文能開啟迷宮入口。 

以下圖為例，$`P_1, P_2, P_3`$ 為圖騰所在位置，每個小方格的邊長為 $`1`$。若詠唱咒文的傳遞範圍為 $`2`$，則符合所求的格子點為圖上圓點所在的位置以及 $`P_1`$，共 $`17`$ 個點。

\begin{figure}[h]
\centering
\begin{tikzpicture}[scale=0.8]
   \draw [-stealth,thick,black] (-4.5,0) -- (5.5,0) node[anchor=west]{\small$x$};
   \draw [-stealth,thick,black] (0,-3.5) -- (0,3.5) node[anchor=south]{\small$y$};
   \foreach \i in {-4,...,-1} {
      \draw [very thin,gray] (\i,-3.5) -- (\i,3.5);
   }
   \foreach \i in {1,...,5} {
      \draw [very thin,gray] (\i,-3.5) -- (\i,3.5);
   }
   \foreach \i in {-3,-2,-1} {
      \draw [very thin,gray] (-4.5,\i) -- (5.5,\i);
   }
   \foreach \i in {1,2,3} {
      \draw [very thin,gray] (-4.5,\i) -- (5.5,\i);
   }
   \filldraw[red] ([xshift=-2pt,yshift=-2pt]0, 0) rectangle ++(4pt,4pt) node[anchor=north east]{\small$P_1$};
   \filldraw[red] ([xshift=-2pt,yshift=-2pt]-1, 0) rectangle ++(4pt,4pt) node[anchor=north east]{\small$P_2$};
   \filldraw[red] ([xshift=-2pt,yshift=-2pt]2, 0) rectangle ++(4pt,4pt) node[anchor=north east]{\small$P_3$};
   \filldraw[black] (-3, 0) circle (2.5pt);
   \filldraw[black] (-2, -1) circle (2.5pt);
   \filldraw[black] (-2, 1) circle (2.5pt);
   \filldraw[black] (-1, -2) circle (2.5pt);
   \filldraw[black] (-1, 2) circle (2.5pt);
   \filldraw[black] (0, -2) circle (2.5pt);
   \filldraw[black] (0, 2) circle (2.5pt);
   \filldraw[black] (1, 0) circle (2.5pt);
   \filldraw[black] (2, -2) circle (2.5pt);
   \filldraw[black] (2, -1) circle (2.5pt);
   \filldraw[black] (2, 1) circle (2.5pt);
   \filldraw[black] (2, 2) circle (2.5pt);
   \filldraw[black] (3, -1) circle (2.5pt);
   \filldraw[black] (3, 0) circle (2.5pt);
   \filldraw[black] (3, 1) circle (2.5pt);
   \filldraw[black] (4, 0) circle (2.5pt);
\end{tikzpicture}
\end{figure}

## 輸入格式

\begin{format}
\f{
$n$ $r$
$x_1$ $y_1$
$x_2$ $y_2$
\vdots
$x_n$ $y_n$
}
\end{format}

- $`n`$ 為圖騰數量
- $`r`$ 為咒文傳遞範圍的距離
- $`(x_i, y_i)`$ 為第 $`i`$ 個圖騰的位置 $`P_i`$

## 輸出格式

\begin{format}
\f{
$\textrm{ans}$
}
\end{format}

- $`\textrm{ans}`$ 為一整數，代表滿足條件的格子點數量

## 測資限制

* $`1 \le n \le 2500`$
* $`1 \le r \le 10`$
* $`-10^6 \le x_i \le 10^6`$
* $`-10^6 \le y_i \le 10^6`$
* 對於所有的 $`i\ne j`$，皆有 $`P_i\ne P_j`$，亦即圖騰位置兩兩相異
* 輸入的數皆為整數

## 範例測試

## 評分說明

本題共有三組子任務，條件限制如下所示。
每一組可有一或多筆測試資料，該組所有測試資料皆需答對才會獲得該組分數。

|  子任務  |  分數  | 額外輸入限制 |
| :------: | :----: | ------------ |
| 1 | {{score.subtask1}} | $`n = 1`$ |
| 2 | {{score.subtask2}} | $`|x_i|\le100`$ 且 $`|y_i|\le100`$ |
| 3 | {{score.subtask3}} | 無額外限制 |
