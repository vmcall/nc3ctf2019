int __stdcall handle_input_array(void *thread_index)
{
  double v1; // st7
  int v3; // eax
  int v4; // edx
  _DWORD *v5; // ecx
  int v6; // edi
  int v7; // esi
  unsigned __int8 *v8; // ecx
  unsigned __int8 v9; // dl
  unsigned int sin_hash; // eax
  unsigned int index; // esi
  double v15; // ST00_8
  double v16; // ST14_8
  char v18; // ST2B_1
  char v19; // bh
  char v20; // bl
  unsigned int v22; // ecx
  unsigned int v23; // edx
  int v24; // [esp+18h] [ebp-14h]
  int v25; // [esp+1Ch] [ebp-10h]
  _DWORD *v26; // [esp+20h] [ebp-Ch]
  double (__stdcall *v27)(double); // [esp+24h] [ebp-8h]
  double (__stdcall *fn_ntdll_sin)(double); // [esp+24h] [ebp-8h]
  char val_48; // [esp+37h] [ebp+Bh]

  
  index = (unsigned int)thread_index;
  // convert index to float
  __asm
  {
    vxorps  xmm0, xmm0, xmm0
    vcvtsi2sd xmm0, xmm0, esi
    vaddsd  xmm0, xmm0, ds:qword_4131D0[eax*8]
    vmovsd  [esp+2Ch+var_2C], xmm0
  }
  // sin(index) * 4096
  v16 = ntddl_sin(LODWORD(v15), HIDWORD(v15)) * 4096.0;
  __asm { vcvttsd2si eax, qword ptr [ebp-18h] }
  val_48 = gentable[(unsigned __int8)gentable_offset + _EAX];
  v18 = input_table[index % (unsigned __int8)byte_432110];
  v19 = input_table[(index + 1) % (unsigned __int8)byte_432110];
  v20 = input_table[(index + 2) % (unsigned __int8)byte_432110];
  // This sets the base+1E008 array
  g_transformed_input[index] = v18 + v19 + (val_48 ^ v20);
  return 0;
}


int __stdcall entrypoint(char *argument)
{
  int v1; // edi
  int v2; // esi
  char *v4; // ecx
  char v5; // al
  _LDR_DATA_TABLE_ENTRY *next_element; // ecx
  _PEB_LDR_DATA *ldr_data; // eax
  void *v8; // edi
  int v9; // esi
  char *v10; // eax
  char *v11; // eax
  char *v12; // edx
  char *v13; // eax
  unsigned __int8 *function_name; // ecx
  unsigned __int8 v15; // dl
  unsigned int RtlAddVectoredExceptionHandler_crc_hash; // eax
  void (__stdcall *RtlAddVectoredExceptionHandler)(_DWORD, void *); // eax
  unsigned int thread_id; // esi
  struct_PEB *v19; // ecx
  _PEB_LDR_DATA *v20; // eax
  int v21; // edi
  int v22; // esi
  _DWORD *v23; // eax
  _LDR_DATA_TABLE_ENTRY *v24; // eax
  _LDR_DATA_TABLE_ENTRY *v25; // edx
  int v26; // eax
  unsigned __int8 *v27; // ecx
  unsigned __int8 v28; // dl
  unsigned int CreateThread_crc_hash; // eax
  int (__cdecl *CreateThread)(_DWORD, _DWORD, int (__stdcall *)(void *), unsigned int, _DWORD, _DWORD); // eax
  unsigned int v31; // esi
  int v32; // ecx
  _DWORD *v33; // ecx
  int v34; // eax
  int v35; // edi
  int v36; // esi
  struct_PEB *v37; // eax
  _LDR_DATA_TABLE_ENTRY *v38; // eax
  _LDR_DATA_TABLE_ENTRY *v39; // edx
  struct_PEB *v40; // eax
  unsigned __int8 *v41; // ecx
  unsigned __int8 v42; // dl
  unsigned int CreateThread_crc_hash_2; // eax
  void (__cdecl *CreateThread_1)(_DWORD, _DWORD, int (__stdcall *)(unsigned int), unsigned int, _DWORD, _DWORD); // eax
  _DWORD *v45; // ecx
  int v46; // eax
  int v47; // edi
  int v48; // esi
  struct_PEB *v49; // eax
  int v50; // eax
  int v51; // edx
  struct_PEB *v52; // eax
  unsigned __int8 *v53; // ecx
  unsigned __int8 v54; // dl
  unsigned int VirtualAlloc_hash; // eax
  int (__cdecl *VirtualAlloc)(_DWORD, signed int, signed int, signed int); // eax
  unsigned int v57; // esi
  int allocated_buffer; // edi
  struct_PEB *v59; // ecx
  _PEB_LDR_DATA *v60; // eax
  int v61; // edi
  void *v62; // esi
  int v63; // eax
  _LDR_DATA_TABLE_ENTRY *v64; // eax
  _LDR_DATA_TABLE_ENTRY *v65; // edx
  _DWORD *v66; // eax
  unsigned __int8 *v67; // eax
  unsigned __int8 v68; // dl
  unsigned int v69; // ecx
  void (__cdecl *unknown_import)(int, unsigned int); // eax
  unsigned int table_index; // ecx
  unsigned int buffer2index; // ecx
  int stream; // eax MAPDST
  unsigned int print_index; // esi
  int v89; // ST08_4
  unsigned int v93; // ecx
  unsigned int v94; // edx
  unsigned int v95; // ecx
  unsigned int v96; // edx
  unsigned int v97; // ecx
  unsigned int v98; // edx
  unsigned int v99; // ecx
  unsigned int v100; // edx
  unsigned int v101; // ecx
  unsigned int v102; // edx
  int v103; // [esp-8h] [ebp-224h]
  int v104; // [esp-4h] [ebp-220h]
  int thread_handles[128]; // [esp+0h] [ebp-21Ch]
  int v106; // [esp+200h] [ebp-1Ch]
  unsigned int v107; // [esp+204h] [ebp-18h]
  _DWORD *v108; // [esp+208h] [ebp-14h]
  struct_PEB *peb; // [esp+20Ch] [ebp-10h]
  _DWORD *v110; // [esp+210h] [ebp-Ch]
  struct_PEB *PEB; // [esp+214h] [ebp-8h]
  _LDR_DATA_TABLE_ENTRY *next_element_copy; // [esp+218h] [ebp-4h]
  char *argumenta; // [esp+224h] [ebp+8h]
  char *argumentb; // [esp+224h] [ebp+8h]
  char *argumentc; // [esp+224h] [ebp+8h]
  char *argumentd; // [esp+224h] [ebp+8h]
  char *argumente; // [esp+224h] [ebp+8h]

  v4 = argument;
  
  // COPY INPUT
  while (v5)
  {
	   v5 = *v4++;
	  input_table[argument - v4] = v5;
  }
  // ADD EXCEPTION HANDLER
  RtlAddVectoredExceptionHandler)(0, exception_handler);

  thread_id = 0;
  
  while (true)
  {
    
    __asm { int     1; - internal hardware - SINGLE-STEP }
    // CREATE INPUT THREADS
    thread_handles[thread_id] = CreateThread(0, 0, handle_input_array, thread_id, 0, 0);
    argumentb = (char *)++thread_id;
    if ( thread_id < 0x80 )
      continue;
    break;
  }
  
  allocated_buffer = VirtualAlloc(0, 0x180, 0x1000, 4);
  v106 = allocated_buffer;
  argumente = 0;
  
  do
  {
    input_array_copy[table_index] = calculated_input_array[table_index];
    calculated_input_array[table_index] ^= 1u;
    ++table_index;
  }
  while ( table_index < 0x80 );
  // Calculate output:
  __asm
  {
    vmovdqa xmm3, ds:some_variable
    vpxor   xmm1, xmm1, xmm1
    vpcmpeqd xmm0, xmm1, xmm1
    vpsubb  xmm2, xmm1, xmm0
  }
  _EDX = 0;
  __asm { vpaddb  xmm4, xmm2, xmm2 }
  do
  {
    __asm
    {
      vmovdqu xmm0, input_array_copy[edx]
      vpsubd  xmm0, xmm0, xmm2
      vpsubw  xmm1, xmm0, xmm4
      vmovdqu xmm0, input_table
      vpshufb xmm0, xmm0, xmm3
      vpaddb  xmm0, xmm1, xmm0
      vpalignr xmm0, xmm0, xmm0, 0Fh
      vpshufb xmm0, xmm0, xmm3
      vmovdqu input_array_copy[edx], xmm0
    }
    buffer2index = 0;
    do
    {
      tmp_buffer[buffer2index] = input_array_copy[buffer2index];
      *(_BYTE *)(buffer2index + allocated_buffer + 0x20) = tmp_buffer[buffer2index];
      ++buffer2index;
    }
    while ( buffer2index < 0x80 );
    _EDX += 0x10;
  }
  while ( _EDX < 0x70 );
  stream = __acrt_iob_func(2);
  std::printf(stream, (int)"Lad os se ...\n");
  print_index = 0;
  do
  {
    v89 = *(unsigned __int8 *)(print_index + allocated_buffer + 0x20);
    stream = __acrt_iob_func(2);
    std::printf(stream, (int)"%c", v89);
    ++print_index;
  }
  while ( print_index < 0x80 );
  stream = __acrt_iob_func(2);
  return std::printf(stream, (int)"\n");
}