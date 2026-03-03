FROM gcc:latest

WORKDIR /app

COPY . .

RUN g++ -std=c++17 -O2 -Wall -o main main.cpp

CMD ["./main"]
