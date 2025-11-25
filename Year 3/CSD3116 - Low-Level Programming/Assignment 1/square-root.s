# square-root.s
# Assembly implementation of square root calculation using successive odd number subtraction
# Author: Bryan Ang Wei Ze
# Date: 2025-09-16

.section .rodata
    # Format string for printf
    format_str: .string "Square root of %u is %u.\n"

.section .text
    .global sq_root_compute_array
    .global sq_root_compute_varargs

# Helper function: compute_square_root
# Input: %edi = unsigned int value
# Output: %eax = square root (rounded down)
compute_square_root:
    # Function prologue - save callee-saved registers
    pushq   %rbx                # Save %rbx (will use it for 'odd')
    
    # Initialize variables
    xorl    %eax, %eax          # root = 0 (return value)
    movl    $1, %ebx            # odd = 1
    
    # Main loop: while (value >= odd)
sqrt_loop:
    cmpl    %ebx, %edi          # compare value with odd
    jb      sqrt_done           # if value < odd, exit loop
    
    subl    %ebx, %edi          # value -= odd
    addl    $2, %ebx            # odd += 2 (next odd number)
    incl    %eax                # ++root
    
    jmp     sqrt_loop           # continue loop

sqrt_done:
    # Function epilogue
    popq    %rbx                # Restore %rbx
    ret                         # return root (in %eax)

# Function: sq_root_compute_array
# Input: %edi = int num_of_elements, %rsi = unsigned int *array_of_elements  
# Output: void (prints results)
sq_root_compute_array:
    # Function prologue
    pushq   %rbp                # Save old base pointer
    movq    %rsp, %rbp          # Set up new base pointer
    pushq   %rbx                # Save callee-saved registers
    pushq   %r12
    pushq   %r13
    
    # Save parameters
    movl    %edi, %r12d         # r12d = num_of_elements
    movq    %rsi, %r13          # r13 = array_of_elements
    xorl    %ebx, %ebx            # ebx = i (loop counter)
    
    # Check if num_of_elements <= 0
    testl   %r12d, %r12d
    jle     array_done          # if num_of_elements <= 0, exit

array_loop:
    # Check loop condition: i < num_of_elements
    cmpl    %r12d, %ebx
    jge     array_done          # if i >= num_of_elements, exit
    
    # Get array[i]
    movl    (%r13, %rbx, 4), %edi   # edi = array_of_elements[i] (4 bytes per int)
    
    # Align stack for function call (subtract 8 to make stack 16-byte aligned)
    subq    $8, %rsp
    
    # Call compute_square_root
    call    compute_square_root     # result in %eax
    
    # Restore stack alignment
    addq    $8, %rsp
    
    # Prepare printf arguments
    movl    (%r13, %rbx, 4), %esi   # esi = array_of_elements[i] (original value)
    movl    %eax, %edx              # edx = square root result
    leaq    format_str(%rip), %rdi  # rdi = format string address
    xorl    %eax, %eax              # eax = 0 (no floating point args)
    
    # Align stack for printf call
    subq    $8, %rsp
    
    # Call printf
    call    printf
    
    # Restore stack
    addq    $8, %rsp
    
    # Increment loop counter
    incl    %ebx                    # i++
    jmp     array_loop

array_done:
    # Function epilogue
    popq    %r13                # Restore callee-saved registers
    popq    %r12
    popq    %rbx
    popq    %rbp                # Restore base pointer
    ret

# Function: sq_root_compute_varargs  
# Input: %edi = first unsigned int, then %esi, %edx, %ecx, %r8d, %r9d, then stack args
# All arguments terminated by 0
# Output: void (prints results)
sq_root_compute_varargs:
    # Function prologue
    pushq   %rbp                # Save old base pointer
    movq    %rsp, %rbp          # Set up new base pointer
    pushq   %rbx                # Save callee-saved registers
    pushq   %r12                # Save register for argument index
    pushq   %r13                # Save register for stack pointer tracking
    
    # Save all register arguments on stack for easy access
    # This simulates what the compiler would do for va_list
    subq    $48, %rsp           # Space for 6 register args (8 bytes each)
    movl    %edi, 0(%rsp)       # Save 1st arg
    movl    %esi, 8(%rsp)       # Save 2nd arg  
    movl    %edx, 16(%rsp)      # Save 3rd arg
    movl    %ecx, 24(%rsp)      # Save 4th arg
    movl    %r8d, 32(%rsp)      # Save 5th arg
    movl    %r9d, 40(%rsp)      # Save 6th arg
    
    # Initialize variables
    movl    $0, %r12d           # r12d = argument index (0, 1, 2, ...)
    leaq    16(%rbp), %r13      # r13 = pointer to stack arguments (after register args)

varargs_loop:
    # Get current argument based on index
    cmpl    $6, %r12d           # Check if we're still in register args
    jae     varargs_stack_arg   # If index >= 6, get from stack
    
    # Get argument from our saved register area
    movl    (%rsp, %r12, 8), %ebx   # ebx = saved_args[index]
    jmp     varargs_process
    
varargs_stack_arg:
    # Calculate stack argument position
    movl    %r12d, %eax         # eax = current index
    subl    $6, %eax            # eax = index - 6 (stack argument number)
    movl    (%r13, %rax, 8), %ebx   # ebx = stack_args[index-6]

varargs_process:
    # Check if current value is 0 (terminator)
    testl   %ebx, %ebx
    jz      varargs_done        # if value == 0, exit
    
    # Calculate square root of current value
    movl    %ebx, %edi          # Pass current value to compute_square_root
    
    # Align stack for function call
    subq    $8, %rsp            # Make stack 16-byte aligned for call
    call    compute_square_root # Result in %eax
    addq    $8, %rsp            # Restore stack
    
    # Print result
    movl    %ebx, %esi          # esi = original value
    movl    %eax, %edx          # edx = square root
    leaq    format_str(%rip), %rdi  # rdi = format string
    xorl    %eax, %eax          # No floating point args
    
    # Align stack for printf call
    subq    $8, %rsp            # Make stack 16-byte aligned for call
    call    printf
    addq    $8, %rsp            # Restore stack
    
    # Move to next argument
    incl    %r12d               # index++
    jmp     varargs_loop

varargs_done:
    # Function epilogue
    addq    $48, %rsp           # Restore stack space for saved args
    popq    %r13                # Restore callee-saved registers
    popq    %r12
    popq    %rbx
    popq    %rbp                # Restore base pointer
    ret
