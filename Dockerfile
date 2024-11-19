FROM alpine
RUN apk update && apk add g++ git
WORKDIR /app
RUN git clone https://github.com/strAngel-010/parprog_shell_sort
WORKDIR /app/parprog_shell_sort
RUN g++ -fopenmp parprog_shell_sort.cpp
VOLUME ["/output"]
CMD ["sh", "-c", "./a.out > /output/result.txt"]
