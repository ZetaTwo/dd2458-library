@echo off
labb%1\%3\labb%1-%2-runner.exe < labb%1\labb%1-%2-runner\Tests\%4.in > labb%1\labb%1-%2-runner\Tests\%4.out
diff labb%1\labb%1-%2-runner\Tests\%4.out labb%1\labb%1-%2-runner\Tests\%4.ans