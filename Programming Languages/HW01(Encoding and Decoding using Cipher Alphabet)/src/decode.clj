; *********************************************
; *  341 Programming Languages                *
; *  Fall 2017                                *
; *  Author: Yakup Genc                       *
; *********************************************

;; utility functions
(load-file "include.clj") ;; "c2i and "i2c"

(use 'clojure.java.io)


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defn encode-word [word cipher alphabet]
	"Encode a word."
		(for [letter word]
			(nth cipher (.indexOf alphabet letter))))

(defn encode-document [filename cipher alphabet]
	"Encode a document."
	(for [word (seq (clojure.string/split (slurp filename) #"\s"))]
		(if (not= (clojure.string/blank? word) true)
			(apply str (encode-word word cipher alphabet)))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defn read-as-list
	"Reads a file containing one word per line and returns a list of words (each word is in turn a list of characters)."
	[filename]
	(let [lines (seq (clojure.string/split-lines (slurp filename)))] ;let lines a sonra yazdigin ifadeyi atar. slurp = read
    (map seq lines))) ; seq aldığı herşeyi listeye atar. ;seq burda map e parametre olarak gider.

;; -----------------------------------------------------
;; HELPERS
;;
;; this two function calculates the all permutations of a seq.
;; taken from https://codereview.stackexchange.com/questions/135737/generate-all-permutations-in-clojure
(defn rotations [a-seq]
  (let [a-vec (vec a-seq)]
    (for [i (range (count a-vec))]
      (concat (subvec a-vec i) (subvec a-vec 0 i)))))

(defn permutations [a-set]
  (if (empty? a-set)
    (list ())
    (mapcat
     (fn [[x & xs]] (map #(cons x %) (permutations xs)))
     (rotations a-set))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defn spell-checker-0 [word dictionary]
  "Perform ordinary search on the dictionary."
	(when (seq dictionary)
	  (if (= word (first dictionary))
			true
      (recur word (next dictionary)))))

(defn spell-checker-1 [word dictionary]
  "Search word in dictionary with using partial with equal function."
	(some (partial = word) dictionary))


;; -----------------------------------------------------
;; DECODE FUNCTIONS
;;
;;------------------------------------------------------

(defn check-cipher-word [cipher encoded alphabet]
	"Converts the encoded word to the plain with using the given cipher."
	(for [letter encoded]
		(nth alphabet (.indexOf cipher letter))))

(defn check-cipher [cipher words dictionary alphabet spell-checker]
  "Converts each given encoded word to plain and checks if they are all in the
  dictionary. Returns # of words that found in the dictionary."
    (loop [[f & r] words counter 0]
  		(if (= (spell-checker (check-cipher-word cipher f alphabet) dictionary) true)
  			(if (= r nil)
  				(+ 1 counter)
  				(recur r (+ 1 counter)))
  			counter))
	)

(defn get-max-cipher [ciphers words dictionary alphabet spell-checker]
  "ciphers:       all possible ciphers.
   words:         encoded words.
   dictionary:    dictionary.
   alphabet:      alphabet.
   spell-checker: the spell checker function.

   This function tries every cipher to find the cipher that generates the max # of correct words in the dictionary."
  (seq (get (last (into (sorted-map) (for [cipher ciphers] [(check-cipher cipher words dictionary alphabet spell-checker) cipher]))) 1)))


(defn Gen-Decoder-A
	[paragraph spell-checker-function alphabet]

  (def words (map seq (seq (clojure.string/split paragraph #"\s"))))
  (def dictionary (read-as-list "dictionary1.txt"))
  (def max-cipher (get-max-cipher (permutations (seq alphabet)) words dictionary alphabet spell-checker-function))
  (println "Found cipher: " max-cipher)

	(fn [encoded-word]
    (apply str (check-cipher-word max-cipher (seq encoded-word) alphabet)))
)

(defn Gen-Decoder-B-0
	[paragraph]
    ;you should implement this function
)

(defn Gen-Decoder-B-1
	[paragraph]
  	;you should implement this function
)

(defn Code-Breaker
	[document decoder]
  	(for [word (map seq (seq (clojure.string/split document #"\s")))]
      (decoder word)
    )
)

;; -----------------------------------------------------
;; Test code...

(defn test_on_test_data
	[]
  (def my_alphabet (seq "abefli"))
  (def my_cipher (seq "bifael"))
  (def file_name "document2.txt")

  ; read document2.txt and encode the all text with given cipher.
  (def encoded-text (encode-document file_name my_cipher my_alphabet))
  ; now save this encoded text to file (document2-encoded.txt)
  (spit "encoded-document.txt" (clojure.string/replace (prn-str encoded-text) #"[\"\(\)]" ""))

  ; generate the functions that decodes the any encoded word. test it.
  (def test_encoded_word "fela")

  (def myFun-0 (Gen-Decoder-A (slurp "encoded-document.txt") spell-checker-0 my_alphabet))
  (println test_encoded_word "converted to" (myFun-0 test_encoded_word) "\n")

  (def myFun-1 (Gen-Decoder-A (slurp "encoded-document.txt") spell-checker-1 my_alphabet))
  (println test_encoded_word "converted to" (myFun-1 test_encoded_word) "\n")

  ; now convert all encoded words in document to the plain.
  (prn (Code-Breaker (slurp "encoded-document.txt") myFun-0))
)

(test_on_test_data)
