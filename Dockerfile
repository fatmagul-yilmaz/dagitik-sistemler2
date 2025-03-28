FROM ubuntu:latest

RUN apt-get update && apt-get install -y \
    build-essential \
    openmpi-bin \
    libopenmpi-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace

COPY matrix_multiplication.c /workspace/

RUN mpicc -fopenmp -o matrix_multiplication matrix_multiplication.c

CMD ["mpirun", "--allow-run-as-root", "--oversubscribe", "-np", "4", "./matrix_multiplication"]
