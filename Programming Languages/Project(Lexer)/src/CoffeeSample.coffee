(deffun2 sumup (x1)
  (if (equal x1 0)
  then 112
  else (+ x1 (sumup (- x1 1)))
  ))
(sumup 889)
