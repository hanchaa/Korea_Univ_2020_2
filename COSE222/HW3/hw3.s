#
#  Author: Juhan Cha
#  Description: Sorting words using bubble sort
#

.global __start

.text
.align 4

__start:
    
    la t0, Input_data
    la t1, Output_data
    
    sub a0, t1, t0      # Input_data 메모리 주소와 Output_data 메모리 주소의 차이를 이용해 Input_data 속에 있는 데이터의 개수를 구함
    srai a0, a0, 2      
    
    mv a1, a0           # 데이터를 옮길 때 사용할 카운터 a1에 저장
    
move_data:
    
    lw s0, 0(t0)        # s0에 Input_data[i] load
    sw s0, 0(t1)        # Output_data[i]에 s0 store
    
    addi t0, t0, 4      # Input_data 메모리 주소 데이터 하나만큼 이동
    addi t1, t1, 4      # Output_data 메모리 주소 데이터 하나만큼 이동
    addi a1, a1, -1     # loop 카운터 감소
    
    bne a1, zero, move_data    # 데이터의 개수만큼 loop 반복


# 버블 소트 알고리즘을 이용
# L0 ~ L3 outer loop
# L1 ~ L2 inner loop    
L0:
    
    beq a0, zero, L4    # 데이터의 개수 만큼 outer loop를 돌면 loop 종료
    la t2, Output_data  # inner loop에서 사용할 메모리 주소 Input_data[0]의 주소로 초기화
    addi a1, a0, -1     # inner loop 실행 횟수를 데이터 개수 - outer loop 수행 횟수 - 1로 설정
    
L1:
    beq a1, zero, L3    # 데이터 개수 - outer loop 수행 횟수 - 1만큼 inner loop를 돌면 loop 종료
    
    lw s0, 0(t2)        # Input_data[j] load
    lw s1, 4(t2)        # Input_data[j+1] load
    
    bgt s0, s1, L2      # Input_data[j] < Input_data[j+1]일 경우 바꿔서 메모리에 저장
    sw s1, 0(t2)
    sw s0, 4(t2)
    
L2:
    
    addi t2, t2, 4      # 메모리 주소 데이터 하나만큼 이동 (j++)
    addi a1, a1, -1     # inner loop 카운터 감소
    j L1                # inner loop 반복
    
L3:    
    
    addi a0, a0, -1     # outer loop 카운터 감소
    j L0                # outer loop 반복
    
L4: 

    nop

.data
.align 4
Input_data: .word 2, 0, -7, -1, 3, 8, -4, 10
            .word -9, -16, 15, 13, 1, 4, -3, 14
            .word -8, -10, -15, 6, -13, -5, 9, 12
            .word -11, -14, -6, 11, 5, 7, -2, -12
Output_data: .word 0, 0, 0, 0, 0, 0, 0, 0
             .word 0, 0, 0, 0, 0, 0, 0, 0
             .word 0, 0, 0, 0, 0, 0, 0, 0
             .word 0, 0, 0, 0, 0, 0, 0, 0