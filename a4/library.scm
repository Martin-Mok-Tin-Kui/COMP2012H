(define > (lambda (x y) (< y x)))
(define >= (lambda (x y) (not (< x y))))
(define <= (lambda (x y) (not (< y x))))
(define = (lambda (x y) (if (< x y) 0 (not (< y x)))))
(define abs (lambda (x) (if (< x 0) (- 0 x) x)))

(define factorial 
  (lambda (x) 
    (if (< x 2) 
	1 
	(* x (factorial (- x 1))))))

(define for-each
  (lambda (f args)
    (if (nullp args)
	(quote ())
	(cons (f (car args)) (for-each f (cdr args))))))    

(define zero? (lambda (n) (= n 0)))
(define list (lambda args args))
(define len
  (lambda (li)
    (define len-iter
      (lambda (li n)
	(if (nullp li)
	    n
	    (len-iter (cdr li) (+ n 1)))))
    (len-iter li 0)))

(define for-each-args
  (lambda n    

    (define test-length
      (lambda (arg-list)
	(define test
	  (lambda (arg-list n)
	    (if (nullp arg-list)
		1
		(if (= n (len (car arg-list)))
		    (test (cdr arg-list) n)
		    0))))
	(test (cdr arg-list) (len (car arg-list)))))

    (define get-first
      (lambda (arg-list)
	(if (nullp arg-list)
	    (quote ())
	    (cons (car (car arg-list)) (get-first (cdr arg-list))))))
    
    (define get-rest
      (lambda (arg-list)
	(if (nullp arg-list)
	    (quote ())
	    (cons (cdr (car arg-list)) (get-rest (cdr arg-list))))))
    
    (define no-args
      (lambda (arg-list)
	(if (nullp (car arg-list))
	    1
	    0)))
    
    (define main
      (lambda n
	(define func (car n))
	(define arg-list (cdr n))
	(if (no-args arg-list)
	    (quote ())
	    (begin (apply func (get-first arg-list))
		   (apply for-each-args (cons func (get-rest arg-list)))))))

    (if (test-length (cdr n))
	(apply main n)
	(print (quote error)))))

(define list-tail
  (lambda (li num)
    (if (zero? num)
	li
	(list-tail (cdr li) (- num 1)))))

(define list-ref
  (lambda (li index)
    (if (zero? index)
	(car li)
	(list-ref (cdr li) (- index 1)))))

(define reverse
  (lambda (li)
    (define reverse-iter
      (lambda (old new)
	(if (nullp old)
	    new
	    (reverse-iter (cdr old) 
			  (cons (car old) new)))))
    (reverse-iter li (quote ()))))

(define and
  (lambda (a b)
    (if a
	(if b
	    1
	    0)
	0)))

(define equal?
  (lambda (lhs rhs)
    (if (and (nump lhs) (nump rhs))
	(= lhs rhs)
	(if (and (symbolp lhs) (symbolp rhs))
	    (= lhs rhs)
	    (if (and (listp lhs) (listp rhs))
		(if (nullp lhs)
		    (nullp rhs)
		    (if (nullp rhs)
			(nullp lhs)
			(and (equal? (car lhs) (car rhs))
			     (equal? (cdr lhs) (cdr rhs)))))
		 0)))))
	    
(define assoc
  (lambda (obj alist)
    (if (nullp alist)
	0
	(if (equal? obj (car (car alist)))
	    (car alist)
	    (assoc obj (cdr alist))))))

(define list-partition
  (lambda (predicate li)
    (define _partition
      (lambda (predi li satisfied unsatisfied)
	(if (nullp li)
	    (cons (reverse satisfied)
		  (cons (reverse unsatisfied)
			(quote ())))
	    (if (predi (car li))
		(_partition predi 
			    (cdr li) 
			    (cons (car li) satisfied)
			    unsatisfied)
		(_partition predi 
			    (cdr li)
			    satisfied
			    (cons (car li) unsatisfied))))))
    (_partition predicate li (quote ()) (quote ()))))

(define even?
  (lambda (num)
    (if (intp num)
	(if (= num (* 2 (/ num 2)))
	    1
	    0)
	0)))

(define odd? (lambda (num) (not (even? num))))
	    
(define list-sort
  (lambda (cmp li)
    (define predicate
      (lambda (elem)
	(if (cmp elem pivot)
	    1
	    0)))

    (define merge-list
      (lambda (lhs rhs pivot merge)
	(if (nullp lhs)
	    (if (nullp pivot)
		(if (nullp rhs)
		    merge
		    (merge-list lhs (cdr rhs) pivot (cons (car rhs) merge)))
		(merge-list lhs rhs (quote ()) (cons pivot merge)))
	    (merge-list (cdr lhs) rhs pivot (cons (car lhs) merge)))))
    
    (if (nullp li)
	li
	(if (= (len li) 1)
	    li
	    (begin
	      (define pivot (car li))
	      (define e (list-partition predicate (cdr li)))
	      (reverse (merge-list (list-sort cmp (car e))
				   (list-sort cmp (car (cdr e)))
				   pivot
				   (quote ()))))))))


     
		
		 
		    
  
