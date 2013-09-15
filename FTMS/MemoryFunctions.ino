void *safeMalloc(size_t size)
{
  void *tmp;
 
  /*unsigned int addr;
  unsigned int *sizePtr;*/
  tmp=malloc(size);
  if(tmp!=NULL)
  {
       
        /*Serial.print("Debug Malloc:Addr: 0x");
        addr=(unsigned int )tmp;
        Serial.print(addr,HEX);
        Serial.print(" Size allocated: ");
       
        sizePtr= (unsigned int *)tmp-1;
        Serial.print(*sizePtr,DEC);
        Serial.print(" Size Requested: ");
        Serial.println(size,DEC);*/
	  //everything is fine
  } else {
	  //mayor ram error
	  exit(1);
  }
 
  return tmp;
}
//Call this function instead of free in caller function
void safeFree(void *block)
{
  /*unsigned int addr;
  unsigned int *sizePtr;
 
  if(block!=NULL)
  {       
        Serial.print("Debug Free:Addr: 0x");
        addr=(unsigned int )block;
        Serial.print(addr,HEX);
        Serial.print(" Size deallocate: ");
        sizePtr= (unsigned int *)block-1;
        Serial.println(*sizePtr,DEC);
 }*/
  free(block);
 
}
