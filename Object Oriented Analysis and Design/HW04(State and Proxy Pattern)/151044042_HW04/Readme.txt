--Programı çalıştırabilmek için öncelikle load balance ekranından verilen
API_KEY için bakiye yüklenmesi gerekmektedir. 
--Bu yüklemeden sonra ana ekrandan graph formatı girilmesi gerekmektedir.
Format için ilk satıra node sayısı girilmelidir.
Daha sonra satır satır edgeler girilmelidir. 
Edgeler oluşturulurken 3. parametre graph ın ağırlığı olmalıdır.
Örnek graph formatı

5  (node sayısı)
0 1 2 (0 dan 1 e 2 ağırlığında bir edge)
0 3 6
1 2 3
1 3 8 
1 4 5
2 4 7
3 4 9
4 2 7