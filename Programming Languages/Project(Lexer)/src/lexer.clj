(require '[clojure.string :as str])

(defn check_token [token patterns]
  "Check one token to see if it is legal in Coffee lang"
  (loop [patterns patterns]
    (if (empty? patterns)
      nil
      (if (.matches token (first patterns))
        true
        (recur (rest patterns))))))

;;;;;;;;;;;;;;;;;;;;;;;;

(defn check_tokens [tokens]
  "Check all tokens"
  (def syntax_check_regexes '("\\(*[a-zA-Z]+[0-9]*[a-zA-Z]*\\)*", "[-]*[1-9]*[0-9]+\\)*", "\\([\\+\\-\\*\\'\\/]", "\\)+"))
  (loop [tokens tokens]
    (if (empty? tokens)
      true
      (if (not (.isEmpty (first tokens)))
        (if (check_token (first tokens) syntax_check_regexes)
          (recur (rest tokens))
          nil)
        (recur (rest tokens))))))

;;;;;;;;;;;;;;;;

(defn extract_identifiers [string wordList]
  "Function to extract identifiers"
  (let [matcher (re-matcher #"[a-zA-Z]+[0-9]*[a-zA-Z]*" string)]
    (loop [match (re-find matcher)
          result []]
      (if-not match
        result
        (recur (re-find matcher)
          (if (not (.contains wordList match))
            (conj result match)
            result))))))

(defn extract_numbers [string]
  "Function to extract numbers"
  (loop [strings (str/split string #"\s")
        result []]
    (if (empty? strings)
      result
      (if (.matches (first strings) "[-]*[1-9]*[0-9]+\\)*")
        (recur (rest strings) (conj result (str/replace (first strings) #"\)" ""))) 
        (recur (rest strings) result)))))

;;;;;;;;;;;;;;;;;;;;;;

(defn lexer [programPath]
  (def programStr (slurp programPath))
  (def wordList '("and", "or", "not", "equal", "append", "concat", "set", "deffun", "for", "while", "if", "then", "else", "true", "false", "null", "+", "'", "-", "/", "*", "(", ")"))
  (let [spelling (check_tokens (str/split programStr #"\s"))]
    (if (= spelling nil)
      (prn "There is a spelling error on the code.")
      (let [words (extract_identifiers programStr wordList)
            numbers (extract_numbers programStr)]
        (println "\nIdentifiers:")
        (println words)
        (println "As set: " (into #{} words))
        (println "")
        (println "Numbers:")
        (println numbers)
        (println "As set: " (into #{} numbers))
        (println "")))))
	
	'(words numbers)


(lexer "CoffeeSample.coffee")