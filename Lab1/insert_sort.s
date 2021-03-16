				
				;##########################################
				;		Lab 01 skeleton
				;##########################################
				
data_to_sort		dcd		34, 23, 22, 8, 50, 74, 2, 1, 17, 40
list_elements		dcd		10
				
main				ldr		r3, =data_to_sort   ; Load the starting address of the first
				;		of element of the array of numbers into r3
				ldr		r4, =list_elements  ; address of number of elements in the list
				ldr		r4, [r4]        	; number of elements in the list
				
				
				add		r5, r3, #400     ; location of first element of linked list - "head pointer"
				;		(note that I assume it is at a "random" location
				;		beyond the end of the array.)
				
				
				;#################################################################################
				;		Include any setup code here prior to loop that loads data elements in array
				;#################################################################################
				
				;		r6 pointer = head
				mov		r6, r5
				
				;		r11 = number of elements in list
				mov		r11, r4
				
				;		Check if there are any elements in the array to begin with
				cmp		r4, #0
				ble		endloop
				
				;		Store the first node
				;		prev
				;		Assuming #-1 stands for null byte
				mov		r7, #-1
				str		r7, [r6]
				
				;		data
				ldr		r7, [r3]
				add		r3, r3, #4
				str		r7, [r6, #4]
				
				;		next
				add		r7, r6, #32
				str		r7, [r6, #8]
				
				add		r6, r6, #32
				sub		r4, r4, #1
				
				;		Check if there is only one element in the list
				cmp		r4, #0
				ble		endloop
				
				
				;#################################################################################
				;		Start a loop here to load elements in the array and add them to a linked list
				;#################################################################################
loop				cmp		r4, #1
				ble		postloop
				
				;		Store it as: prev, data, next
				;		prev
				sub		r7, r6, #32
				str		r7, [r6]
				
				;		data
				ldr		r7, [r3]
				add		r3, r3, #4
				str		r7, [r6, #4]
				
				;		next
				add		r7, r6, #32
				str		r7, [r6, #8]
				
				;		Store
				
				add		r6, r6, #32     	; every time you create a new struct, add 32 to
				;		starting address of last struct to mimic
				;		non-contiguous memory locations
				;		I assume address of last struct is in r6
				;		you DO NOT need to make this assumption
				
				sub		r4, r4, #1
				b		loop
				
postloop   	 ;   	 Store the last node
				;		prev
				sub		r7, r6, #32
				str		r7, [r6]
				
				;		data
				ldr		r7, [r3]
				add		r3, r3, #4
				str		r7, [r6, #4]
				
				;		next
				;		Assuming #-1 stands for null byte
				mov		r7, #-1
				str		r7, [r6, #8]
				
				;		r12 is the next open spot in memory
				add		r12, r6, #12
endloop
				
				
				
				
				
				
				;====================================================================
				;		Insertion Sort
				;====================================================================
				;		Perform Insertion Sort :)
				;		r3 = j
				;		r4 = i
				;		r10 = key
				;		r13 = array[i]
				
				mov		r3, #1
sortFor		; Outer for loop
				cmp		r3, r11
				bge		endSort
				
				;		Find array[j]
				mov		r6, r5
				mov		r7, #0
				
sortFindLoop1		cmp		r7, r3
				ble		endSortFindLoop1
				;		Load the next pointer into r6
				ldr		r6, [r6, #8]
				add		r7, r7, #1
				b		sortFindLoop1
				
endSortFindLoop1
				;		key = array[j]
				ldr		r10, [r6, #4]
				
				;		i = j-1
				sub		r4, r3, #1
				
sortWhile			mov		r7, #0
				cmp		r4, r7
				blt		endSortWhile
				;		Find array[i]
				mov		r6, r5
				mov		r7, #0
				
sortFindLoop2		cmp		r7, r3
				bge		endSortFindLoop2
				;		Load the next pointer into r6
				ldr		r6, [r6, #8]
				add		r7, r7, #1
				b		sortFindLoop2
				
endSortFindLoop2
				ldr		r13, [r6, #4]
				;		check array[i] > key
				cmp		r13, r10
				ble		endSortWhile
				
				;		Perform swap!!!
				mov		r1, r4
				add		r2, r4, #1
				bl		swap
				;		i = i-1
				sub		r4, r4, #1
				b		sortWhile
				
endSortWhile		; Perform another swap!!!! :)
				mov		r1, r3
				add		r2, r4, #1
				bl		swap
				;		j++
				add		r3, r3, #1
				b		sortFor
				
				
endSort			bl		print
				b		done
				
				
				
				
				
				
				
				
				
				
				
				
				;#################################################################################
				;		Add insert, swap, delete functions
				;#################################################################################
insert   	 	; Insert function
				;		parameters:
				;		r1 - index
				;		r2 - value
				
				;		If inserting at first element
				cmp		r1, #0
				beq		insertFirst
				
				mov		r6, r5
				mov		r7, #1
				;		preserve index
				mov		r10, r1
				
insLoop			cmp		r7, r1
				bge		endInsLoop
				;		Load the next pointer into r6
				ldr		r6, [r6, #8]
				sub		r1, r1, #1
				b		insLoop
				
endInsLoop    ; Load pointer to current next into r9
				ldr		r9, [r6, #8]
				
				;		Set new next to next open memory address
				str		r12, [r6, #8]
				
				;		new node prev
				str		r6, [r12]
				
				;		new node data
				str		r2, [r12, #4]
				
				;		Check if inserting at the last element
				cmp		r10, r11
				beq		insertLast
				
				;		new node next
				str		r9, [r12, #8]
				
				;		Store r12 pointer into r9's prev
				str		r12, [r9]
				
				;		Increment r12 to be next open spot in memory
				add		r12, r6, #12
				
				;		Increment element counter
				add		r11, r11, #1
				
				;		Return to caller
				mov		pc, lr
				
insertFirst	; Insert new node 'before' r5, set r5 as memory address
				;		new node prev = null
				mov		r7, #-1
				str		r7, [r12]
				
				;		new node data
				str		r2, [r12, #4]
				
				;		new node next = previous head
				str		r5, [r12, #8]
				
				;		next node prev = new node
				str		r12, [r5]
				
				;		New head node = r12
				mov		r5, r12
				
				;		Increment r12 to be next open spot in memory
				add		r12, r6, #12
				
				;		Increment element counter
				add		r11, r11, #1
				
				;		Return to caller
				mov		pc, lr
				
insertLast	; Insert after last element
				;		new node next
				mov		r7, #-1
				str		r7, [r12, #8]
				
				;		Increment r12 to be next open spot in memory
				add		r12, r6, #12
				
				;		Increment element counter
				add		r11, r11, #1
				
				;		Return to caller
				mov		pc, lr
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
swap   		 ; Swap function
				;		parameters:
				;		r1 - index1
				;		r2 - index2
				
				;		Find first index's memory address
				mov		r6, r5
				mov		r7, #0
				
swapLoop1			cmp		r7, r1
				bge		endSwapLoop1
				;		Load the next pointer into r6
				ldr		r6, [r6, #8]
				sub		r1, r1, #1
				b		swapLoop1
				
endSwapLoop1	; Find second index's memory address
				mov		r8, r5
				mov		r7, #0
				
swapLoop2			cmp		r7, r2
				bge		endSwapLoop2
				;		Load the next pointer into r8
				ldr		r8, [r8, #8]
				sub		r2, r2, #1
				b		swapLoop2
				
endSwapLoop2		; Check if nodes are contiguous (need to do something different if they are)
				ldr		r7, [r6, #8]
				cmp		r7, r8
				bne		checkContiguous2
				
				;		2nd->prev = 1st->prev,
				;		2nd->next = 1st
				;		1st->prev = 2nd
				;		1st->next = 2nd->next
				ldr		r9, [r8, #8]
				str		r9, [r6, #8]
				str		r6, [r8, #8]
				
				ldr		r9, [r6]
				str		r9, [r8]
				str		r8, [r6]
				b		checkPrev1
				
checkContiguous2	ldr		r9, [r8, #8]
				cmp		r9, r6
				bne		normalSwap
				
				
				;		1st >prev = 2nd->prev,
				;		1st->next = 2nd
				;		2nd->prev = 1st
				;		2nd->next = 1st->next
				ldr		r7, [r6, #8]
				str		r7, [r8, #8]
				str		r8, [r6, #8]
				
				ldr		r7, [r8]
				str		r7, [r6]
				str		r6, [r8]
				
				b		checkPrev1
				
				
normalSwap		; Swap the pointers
				;		Swap node prevs
				ldr		r7, [r6]
				ldr		r9, [r8]
				str		r9, [r6]
				str		r7, [r8]
				
				;		Swap node nexts
				ldr		r7, [r6, #8]
				ldr		r9, [r8, #8]
				str		r9, [r6, #8]
				str		r7, [r8, #8]
				
checkPrev1	; prev->next = cur
				;		First check if null
				mov		r7, #-1
				ldr		r9, [r6]
				cmp		r7, r9
				beq		newHead1
				
				;		if not null,
				str		r6, [r9, #8]
				b		checkPrev2
				
newHead1			; Set the head to be the new thing idk man
				mov		r5, r6
				
checkPrev2	; prev->next = cur
				;		First check if null
				mov		r7, #-1
				ldr		r9, [r8]
				cmp		r7, r9
				beq		newHead2
				
				;		if not null,
				str		r8, [r9, #8]
				b		checkNext1
				
newHead2			; Set the head to be the new thing idk man
				mov		r5, r8
				
				
checkNext1	; next->prev = cur
				;		First check if null
				mov		r7, #-1
				ldr		r9, [r6, #8]
				cmp		r7, r9
				beq		checkNext2
				
				;		if not null,
				str		r6, [r9]
				
				
checkNext2	; next->prev = cur
				;		First check if null
				mov		r7, #-1
				ldr		r9, [r8, #8]
				cmp		r7, r9
				beq		endSwap
				
				;		if not null,
				str		r8, [r9]
				
				
				;		Return
endSwap			mov		pc, lr
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
delete   	 ; Delete function
				;		parameters:
				;		r1 - index
				
				mov		r6, r5
				mov		r7, #0
				;		preserve index for checking if at last element later
				add		r10, r1, #1
				
				;		If deleting first element
				cmp		r1, #0
				beq		delFirst
				
delLoop			cmp		r7, r1
				bge		endDelLoop
				;		Load the next pointer into r6
				ldr		r6, [r6, #8]
				sub		r1, r1, #1
				b		delLoop
				
endDelLoop    ;		Check if deleting the last element
				cmp		r10, r11
				beq		delLast
				
				;		Load previous ptr into r9
				ldr		r9, [r6]
				;		Load next ptr into r10
				ldr		r10, [r6, #8]
				
				;		Store ptr in r10 as r9's next
				str		r10, [r9, #8]
				;		Store ptr in r9 as r10's prev
				str		r9, [r10]
				
				;		Decrement element counter
				sub		r11, r11, #1
				
				;		Return to caller
				mov		pc, lr
				
delFirst		; Delete the first element
				;		Just set next element's previous to -1
				ldr		r6, [r6, #8]
				mov		r7, #-1
				str		r7, [r6]
				
				;		Set cur element as head
				mov		r5, r6
				
				;		Decrement element counter
				sub		r11, r11, #1
				
				;		Return to caller
				mov		pc, lr
				
delLast		; Delete the last element
				;		Just set the previous element's next to -1
				ldr		r6, [r6]
				mov		r7, #-1
				str		r7, [r6, #8]
				
				;		Decrement element counter
				sub		r11, r11, #1
				
				;		Return to caller
				mov		pc, lr
				
				
print		; Function to print the list
				mov		r6, r5
				ldr		r0, [r6, #4] ; First element in list
				ldr		r6, [r6, #8] ; Check if next is null
				cmp		r6, #-1
				beq		end_print ; only one element in list
				
print_loop		ldr		r0, [r6, #4]
				ldr		r6, [r6, #8]
				cmp		r6, #-1
				beq		end_print
				b		print_loop
				
end_print			mov		pc, lr
				
				
done				end
