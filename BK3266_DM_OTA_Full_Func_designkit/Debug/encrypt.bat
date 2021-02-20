TARGET_NAME=BK3266_DM_Full_Func_designkit

if [ 0"$HAVE_RUN_THIS_SCRIPT_FILE" = "0" ];then
    export HAVE_RUN_THIS_SCRIPT_FILE=0
fi

if [ $HAVE_RUN_THIS_SCRIPT_FILE -eq 0 ];then
    export HAVE_RUN_THIS_SCRIPT_FILE=1

    ba-elf-objdump -d     ${TARGET_NAME}.elf    > ${TARGET_NAME}.dmp
    ba-elf-nm             ${TARGET_NAME}.elf    > ${TARGET_NAME}.map
    ba-elf-readelf.exe    ${TARGET_NAME}.elf -a > 0_section_information.txt
    #ba-elf-nm -r          ${TARGET_NAME}.elf    > 1_reverse_sort_symbol.txt
    #ba-elf-nm --size-sort ${TARGET_NAME}.elf    > 2_symbol_by_size.txt
    #ba-elf-nm -p          ${TARGET_NAME}.elf    > 3_no_sort_symbol.txt
    #ba-elf-nm -n          ${TARGET_NAME}.elf    > 4_numeric_sort_symbol.txt
    #ba-elf-nm -l          ${TARGET_NAME}.elf    > 5_symbol_and_line_number.txt
    #ba-elf-nm -g          ${TARGET_NAME}.elf    > 6_external_symbol.txt
    #ba-elf-nm -a          ${TARGET_NAME}.elf    > 7_debug_symbol.txt
    #ba-elf-nm -u          ${TARGET_NAME}.elf    > 8_undefined_symbol.txt
    #ba-elf-nm -S          ${TARGET_NAME}.elf    > 9_print_size_defined_symbol.txt

    ba-elf-objcopy -O binary ${TARGET_NAME}.elf  ${TARGET_NAME}.bin

    ./encrypt ${TARGET_NAME}.bin 00000000

    cp -f ../ram.ld      ../ram.ld.bak
    cp -f ${TARGET_NAME}.bin ${TARGET_NAME}.bin.bak
    cp -f ${TARGET_NAME}.elf ${TARGET_NAME}.elf.bak

    echo "====================================="
    echo "Building ${TARGET_NAME}_1st.bin"
    echo "====================================="
    
    cp -f ${TARGET_NAME}.bin ${TARGET_NAME}_1st.bin

    echo "====================================="
    echo "Building ${TARGET_NAME}_2nd.bin"
    echo "====================================="

    cp -f ../ram_2nd.ld  ../ram.ld
    rm -f /F /Q ${TARGET_NAME}.bin
    rm -f /F /Q ${TARGET_NAME}.elf
    make        ${TARGET_NAME}.elf
    ba-elf-objcopy -O binary ${TARGET_NAME}.elf  ${TARGET_NAME}.bin
    cp -f ${TARGET_NAME}.bin ${TARGET_NAME}_2nd.bin

    mv -f ../ram.ld.bak  ../ram.ld
    mv -f ${TARGET_NAME}.bin.bak ${TARGET_NAME}.bin
    mv -f ${TARGET_NAME}.elf.bak ${TARGET_NAME}.elf
fi
