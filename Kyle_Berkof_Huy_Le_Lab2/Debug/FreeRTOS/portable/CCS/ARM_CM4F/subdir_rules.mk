################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/portable/CCS/ARM_CM4F/port.obj: C:/Users/kberk/OneDrive/Documents/School/ECE\ 3849\ -\ Real-Time\ Embedded\ Systems/Labs/Lab\ 2/lab2Workspace/FreeRTOS/portable/CCS/ARM_CM4F/port.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1281/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/kberk/OneDrive/Documents/School/ECE 3849 - Real-Time Embedded Systems/Labs/Lab 2/lab2Workspace/Kyle_Berkof_Huy_Le_Lab2" --include_path="C:/ti/TivaWare_C_Series-2.2.0.295/driverlib" --include_path="C:/ti/TivaWare_C_Series-2.2.0.295/utils" --include_path="C:/ti/TivaWare_C_Series-2.2.0.295" --include_path="C:/Users/kberk/OneDrive/Documents/School/ECE 3849 - Real-Time Embedded Systems/Labs/Lab 2/lab2Workspace/FreeRTOS/include" --include_path="C:/Users/kberk/OneDrive/Documents/School/ECE 3849 - Real-Time Embedded Systems/Labs/Lab 2/lab2Workspace/FreeRTOS/portable/CCS/ARM_CM4F" --include_path="C:/ti/ccs1281/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --define=ccs="ccs" --define=PART_TM4C1294NCPDT -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="FreeRTOS/portable/CCS/ARM_CM4F/port.d_raw" --obj_directory="FreeRTOS/portable/CCS/ARM_CM4F" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

FreeRTOS/portable/CCS/ARM_CM4F/portasm.obj: C:/Users/kberk/OneDrive/Documents/School/ECE\ 3849\ -\ Real-Time\ Embedded\ Systems/Labs/Lab\ 2/lab2Workspace/FreeRTOS/portable/CCS/ARM_CM4F/portasm.asm $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1281/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/kberk/OneDrive/Documents/School/ECE 3849 - Real-Time Embedded Systems/Labs/Lab 2/lab2Workspace/Kyle_Berkof_Huy_Le_Lab2" --include_path="C:/ti/TivaWare_C_Series-2.2.0.295/driverlib" --include_path="C:/ti/TivaWare_C_Series-2.2.0.295/utils" --include_path="C:/ti/TivaWare_C_Series-2.2.0.295" --include_path="C:/Users/kberk/OneDrive/Documents/School/ECE 3849 - Real-Time Embedded Systems/Labs/Lab 2/lab2Workspace/FreeRTOS/include" --include_path="C:/Users/kberk/OneDrive/Documents/School/ECE 3849 - Real-Time Embedded Systems/Labs/Lab 2/lab2Workspace/FreeRTOS/portable/CCS/ARM_CM4F" --include_path="C:/ti/ccs1281/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --define=ccs="ccs" --define=PART_TM4C1294NCPDT -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="FreeRTOS/portable/CCS/ARM_CM4F/portasm.d_raw" --obj_directory="FreeRTOS/portable/CCS/ARM_CM4F" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


