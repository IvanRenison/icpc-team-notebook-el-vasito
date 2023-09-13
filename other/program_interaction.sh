mkfifo fifo
(./solution < fifo) | (./interactor > fifo)