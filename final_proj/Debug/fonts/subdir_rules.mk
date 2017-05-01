################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
fonts/fontfixed6x8.obj: ../fonts/fontfixed6x8.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"/Applications/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --include_path="/Users/joshuasurette/Desktop/SmartStreetlights/final_proj" --include_path="/Users/joshuasurette/ti/tirex-content/simplelink_msp432_sdk_1_20_00_45/source" --include_path="/Users/joshuasurette/ti/tirex-content/simplelink_msp432_sdk_1_20_00_45/source/third_party/CMSIS/Include" --include_path="/Applications/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --advice:power="all" --advice:power_severity=suppress --define=__MSP432P401R__ -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="fonts/fontfixed6x8.d" --obj_directory="fonts" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


