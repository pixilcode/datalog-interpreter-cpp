#lang racket

(define (template-replace template replacements)
  (for/fold ([template template])
            ([replacement (in-list replacements)]
             #:do [(define template-text (first replacement))
                   (define template-replacement (second replacement))])
    (string-replace template
                    (string-append "{{" template-text "}}")
                    template-replacement)))

(define (generate-from-template template-path output-path replacements)
  (define template-string (file->string template-path))
  (define output-file-contents (template-replace template-string replacements))
  (display-to-file output-file-contents
                   output-path
                   #:mode 'text
                   #:exists 'error))

(define
  (generate-single-char-automaton token-name
                                  character
                                  [all-caps-name (string-upcase token-name)])
  (define test-name (string-downcase token-name))
  (define replacements `(("token-name" ,token-name)
                         ("character" ,character)
                         ("all-caps-name" ,all-caps-name)
                         ("test-name" ,test-name)))

  (generate-from-template "TemplateSingleCharAutomaton.h.template"
                          (string-append token-name "Automaton.h")
                          replacements)
  (generate-from-template "TemplateSingleCharAutomaton.cpp.template"
                          (string-append token-name "Automaton.cpp")
                          replacements))


(define (generate-all-single-chars) (for-each
                                     (lambda (it) (apply generate-single-char-automaton it))
                                     '(("Colon" ":")
                                       ("Comma" ",")
                                       ("Period" ".")
                                       ("QuestionMark" "?" "Q_MARK")
                                       ("LeftParen" "(" "LEFT_PAREN")
                                       ("RightParen" ")" "RIGHT_PAREN")
                                       ("Multiply" "*")
                                       ("Add" "+"))))

(define (generate-keyword-automaton token-name)
  (define all-caps-name (string-upcase token-name))
  (define test-name (string-downcase token-name))
  (define token-length (number->string (string-length token-name)))
  (define replacements `(("token-name" ,token-name)
                         ("token-length" ,token-length)
                         ("all-caps-name" ,all-caps-name)
                         ("test-name" ,test-name)))

  (generate-from-template "TemplateKeywordAutomaton.h.template"
                          (string-append token-name "Automaton.h")
                          replacements)
  (generate-from-template "TemplateKeywordAutomaton.cpp.template"
                          (string-append token-name "Automaton.cpp")
                          replacements))

(define (generate-all-keywords) (for-each generate-keyword-automaton
                                          '("Schemes" "Facts" "Rules" "Queries")))