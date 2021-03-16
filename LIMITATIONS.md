# Limitations



##CGSW1

###Operations:

1. Addition:
    - Not sure what is the correct behaviour. Should it wrap around p?  But deciphered
      answer are wrapped around q. Is the translation from q to p supported correctly in 
      the scheme now? Should we do round(f)? or should be do divide q then multiply p? 
      In that case, the divide operation has to be the multiplicative inverse?
    - Another ways to solve this is to ensure the p to be >> than actual plaintext space, 
      probably a multiple of the actual plaintext space by multiplicative (addition too?) depth.
      
2. Substration:
    - Not sure how the wrap around is handled here actually. Similar to above.
    

3. Multiplication with GSW:

4. Multiplication with CGSW: