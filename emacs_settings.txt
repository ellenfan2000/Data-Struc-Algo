(package-initialize)

;; Comment this next line if you do not want line numbers on the left side
(global-linum-mode 1)


;; Sets our compilation key binding to C-c C-v
(global-set-key "\C-c\C-v" 'compile)


(setq line-number-mode t)
(setq column-number-mode t)
(display-time)
(global-font-lock-mode t)
(setq font-lock-maximum-decoration t)

;;This makes rainbow delimiters mode the default.
;;comment out to turn it off.
(add-hook 'find-file-hook 'rainbow-delimiters-mode-enable)

;;Want electric pair mode? Uncomment the next line
;(electric-pair-mode)

;;Want to turn off show paren mode? Comment out the below line.
(show-paren-mode)


(global-set-key "\C-x\C-g" 'goto-line)

;; these change the colors for rainbow delimters.   Dont' change them here!
;; change them in M-x customize
(custom-set-faces
 ;; custom-set-faces was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(rainbow-delimiters-depth-2-face ((t (:inherit rainbow-delimiters-base-face :foreground "color-153"))))
 '(rainbow-delimiters-depth-3-face ((t (:inherit rainbow-delimiters-base-face :foreground "color-92"))))
 '(rainbow-delimiters-depth-5-face ((t (:inherit rainbow-delimiters-base-face :foreground "color-167"))))
 '(rainbow-delimiters-depth-6-face ((t (:inherit rainbow-delimiters-base-face :foreground "color-40"))))
 '(rainbow-delimiters-unmatched-face ((t (:inherit rainbow-delimiters-base-face :background "red" :foreground "black")))))

;; Automatically set compilation mode to
;; move to an error when you move the point over it
;; Dont want this behavior? commend out the next 4 lines.
(add-hook 'compilation-mode-hook
 (lambda () 
   (progn
     (next-error-follow-minor-mode))))

;;Automatically go to the first error
;;Dont want this behavior? comment out next line
(setq compilation-auto-jump-to-first-error t)


;;This prevents gdb from getting a dedicated window,
;;which is generally super annoying
;; (defun set-window-undedicated-p (window flag)
;;   "Never set window dedicated."
;;   flag)
;;(advice-add 'set-window-dedicated-p :override #'set-window-undedicated-p)


;;Autocompletion from company
(require 'company)
(require 'company-rtags)
;; This turns on autocomplete globally. Want to turn it off (why???) comment out next line.
(global-company-mode)
(add-to-list 'company-backends 'company-c-headers)

;;clang-format to format file reasonably.  Do NOT turn off!
(require 'clang-format)
(global-set-key [C-M-tab] 'clang-format-region)
(add-hook 'c-mode-common-hook
          (function (lambda ()
                    (add-hook 'write-contents-functions
                              (lambda() (progn (clang-format-buffer) nil))))))

(add-hook 'cpp-mode-common-hook
          (function (lambda ()
                      (add-hook 'write-contents-functions
                                (lambda() (progn (clang-format-buffer) nil))))))

;; Flycheck: show you whats wrong while you write
;; Dont want?  comment out next 3 lines.
;; Dont want popups with whats wrong?  comment out third line only
(require 'flycheck)
(global-flycheck-mode)
(flycheck-popup-tip-mode)


;; This does the popup menu for M-y.
;; if you dont want it, you can comment out the next 12 lines.
(require 'popup-kill-ring)
(defun drew-popup-kill-ring(&optional arg)
  (interactive "*p")
  (if  (eq last-command 'yank)
      (let ((inhibit-read-only t)
            (before (< (point) (mark t))))
        (if before
            (funcall (or yank-undo-function 'delete-region) (point) (mark t))
          (funcall (or yank-undo-function 'delete-region) (mark t) (point)))))
  (popup-kill-ring))
(global-set-key "\M-y" 'drew-popup-kill-ring)
(setq popup-kill-ring-interactive-insert t)



;;This just shows your grade.txt files in color and read only.
(defun colorize-grade-txt ()
  "Make a grade.txt file show colors, then set read only."
  (interactive)
  (if (or (string= (buffer-name) "grade.txt")
          (string-prefix-p (buffer-name) "grade.txt<"))
      (progn (let ((inhibit-read-only t))
               (ansi-color-apply-on-region (point-min) (point-max)))
             (set-buffer-modified-p nil)
             (read-only-mode t))))

(add-hook 'find-file-hook 'colorize-grade-txt)
;;company mode doesnt play well with gdb mode.  Leave this here
(add-hook 'gud-mode-hook (lambda() (company-mode 0)))
(add-to-list 'auto-mode-alist '("\\.h" . c++-mode))


;;Gdb window layout stuff
(setq gdb-many-windows t
      gdb-use-separate-io-buffer t)
(advice-add 'gdb-setup-windows :after (lambda() (set-window-dedicated-p (selected-window) t)))
     	
(defconst gud-windown-register 123456)

(defun gud-quit()
  (interactive)
  (gud-basic-call "quit"))

(add-hook 'gud-mode-hook
          (lambda()
            (gud-tooltip-mode)
            (window-configuration-to-register gud-windown-register)
            (local-set-key (kbd "C-q") 'gud-quit)))

(advice-add 'gud-sentinel :after
            (lambda (proc msg)
              (when (memq (process-status proc) '(signal exit))
                (jump-to-register gud-windown-register)
                (bury-buffer))))
(custom-set-variables
 ;; custom-set-variables was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(python-shell-interpreter "python3"))
