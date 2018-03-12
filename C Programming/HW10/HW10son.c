/*************************************************************
 *                                                           *
 * HW10                                                      *
 * Student Name: Elif Seyma ARMAGAN                          *
 * Student ID  : 151044042                                   *
 * Date        : 02/05/2016                                  *
 * Description : Bu program temelde bir binary file okur bu  * 
 * 				 binary file kullanilarak istenilen verileri *
 *	             buradan okur ve .txt formatinda bir dosyaya *
 *				 yazar.                                      *
 *                                                           *
 *************************************************************/

/* Kutuphanelerin tanitilmasi */
#include <stdio.h>
#include <stdlib.h>

#define MAX 100 /* Array icin max eleman sayisi */

/* Ogrenciler */
typedef struct
{
	int  studentID;
	char studentName[30];
	char studentSurname[30];
}student; 

/* Ogretim uyeleri */
typedef struct
{
	char lecturerDegree[30];
	int  lecturerID;
	char lecturerName[30];
	char lecturerSurname[30];
} lecturer; 

/* Dersler */
typedef struct 
{
	int  lectureCode;
	char lectureName[30];
	int  lecturerID; 
}lecture; 

/* Ders akisi */
typedef struct 
{
	char classroomName[30];
	char day[30];
	int  startTime;
	int  durationTime;
	int  lectureCode;
}schedule; 

/* Alinan dersler */
typedef struct 
{
	int studentID;
	int lectureCode;
}courseStudent; 


/* Prototipler */
void readBinFile(FILE * file, student * students, lecturer * lecturers, lecture * lectures,
	 schedule * schedules, courseStudent * coursesStudent, int * studentNum, int * lecturerNum, 
	 int * lectureNum, int * scheduleNum, int * courseStudentNum);
void writeOutputFile(FILE * file, student * students, lecturer * lecturers, lecture * lectures,
	 schedule * schedules, courseStudent * coursesStudent, int * studentNum, int * lecturerNum, 
	 int * lectureNum, int * scheduleNum, int * courseStudentNum);
lecturer * findLecturer(lecturer * lecturers, int size, int ID);
int getStudentNumOfLecture(courseStudent * coursesStudent, int size, int lectureCode);
int getLectureOfStudent(courseStudent * coursesStudent, int size, int studentID );


int main ()
{
	/* START OF MAIN */
	
	/* Degiskenlerin olusturulmasi */
	student students[MAX];
	lecturer lecturers[MAX];
	lecture lectures[MAX];
	schedule schedules[MAX];
	courseStudent coursesStudent[MAX];

	int studentNum, lecturerNum, lectureNum, scheduleNum, courseStudentNum;

	/* FILE tipinde degiskenlerin olusturulmasi */
	FILE *iptr;
	FILE *optr;

	/* input.dat dosyasi okunmak icin acilir. Eger NULL ise uyari verir. */
	if ((iptr = fopen( "input.dat", "rb" )) == NULL )
	{
		printf( "Dosya acilamadi.\n" );W
		return (0);
	}
	
	/* output.txt dosyasi yazilmak icin acilir. Eger NULL ise uyari verir.*/
	if ((optr = fopen( "output.txt", "w" )) == NULL )
	{
		printf( "Dosya acilamadi.\n" );
		return (0);
	}
	
	else
	{
		/* Verilen binary dosyayi okuyan ve output dosyasini hazirlayan fonksiyonlarin cagirilmasi */
		readBinFile(iptr, students, lecturers, lectures, schedules, coursesStudent, &studentNum,
	    &lecturerNum, &lectureNum, &scheduleNum, &courseStudentNum);
		writeOutputFile(optr, students, lecturers, lectures, schedules, coursesStudent, &studentNum,
		&lecturerNum, &lectureNum, &scheduleNum, &courseStudentNum);

		/* Acilmis olan dosyalarin kapatilmasi */
		fclose(iptr);
		fclose(optr);
	}
	return (0);

	/* END OF MAIN */
}

/* Verilen binary file i okuyan fonksiyon */
void readBinFile(FILE * file, student * students, lecturer * lecturers, lecture * lectures, schedule * schedules, courseStudent * coursesStudent,
	 int * studentNum, int * lecturerNum, int * lectureNum, int * scheduleNum, int * courseStudentNum)
{
	/****************************************************************************************************
	 *  Bu fonksiyon su sekilde calisir. İlk calistiginda input.dat icindeki ilk veriyi okur.           *
	 *  Bu bir sayidir ve ilk okudugumuz sayi kac tane student tipinde students okuyacagimizi belirler. *
	 *  İlk okudugumuz sayi kadar students okuduktan sonra karsimiza bir tane daha sayi cikar.          *
	 *  Bu sayi da kac tane lecturer tipinde lectures okuyacagimizi belirler. Bu fonksiyon              *
	 *  bu sekilde istenilen sayi adedince her turu okuyana kadar devam eder.                           *                       
     ****************************************************************************************************/	
	fread(studentNum, sizeof(int), 1, file);
	fread(students, sizeof(student), *studentNum, file);

	fread(lecturerNum, sizeof(int), 1, file);
	fread(lecturers, sizeof(lecturer), *lecturerNum, file);

	fread(lectureNum, sizeof(int), 1, file);
	fread(lectures, sizeof(lecture), *lectureNum, file);

	fread(scheduleNum, sizeof(int), 1, file);
	fread(schedules, sizeof(schedule), *scheduleNum, file);

	fread(courseStudentNum, sizeof(int), 1, file);
	fread(coursesStudent, sizeof(courseStudent), *courseStudentNum, file);
}

/* Bir file a istenilen verileri yazan fonskyon */
void writeOutputFile(FILE * file, student * students, lecturer * lecturers, lecture * lectures, schedule * schedules, courseStudent * coursesStudent,
	int * studentNum, int * lecturerNum, int * lectureNum, int * scheduleNum, int * courseStudentNum)
{
	int i,j,k,num,res, temp;
	lecturer * lec;
	temp = 0;

	fprintf(file, "Lecture-Lecturer\n");
	for (i = 0; i < * lectureNum; i++)
	{
		/* Lecture name in yazilmasi */
		fprintf(file, "%s ", lectures[i].lectureName); 
		/* Lecture i veren lecturer i bulan fonksiyonun cagrilmasi ve lecturer degerinin elde edilmesi*/
		lec = findLecturer(lecturers, *lecturerNum, lectures[i].lecturerID);
		/* Lecturer degerinin yazilmasi */
		fprintf(file, "%s %s ", lec->lecturerName, lec->lecturerSurname);
		/* O lecture i alan toplam ogrenci sayisini bulan fonksiyonun cagrilmasi ve degerin elde edilmesi */
		num = getStudentNumOfLecture(coursesStudent, *courseStudentNum, lectures[i].lectureCode);
		/* O dersi alan ogrenci sayisinin yazdirilmasi */
		fprintf(file, "%d\n", num );
	}
	
	fprintf(file, "\nStudent-Lecture\n");
	for(i = 0; i< * studentNum; i++)
	{
		/* Student ID Name ve Surname inin yazilmasi */
		fprintf(file, "%d ", students[i].studentID);
		fprintf(file, "%s ", students[i].studentName);
		fprintf(file, "%s ", students[i].studentSurname);
		/* Bir ogrencinin kac ders aldigini bulan fonksiyonun cagrilmasi ve degerin elde edilmesi */
		res = getLectureOfStudent(coursesStudent, *courseStudentNum, students[i].studentID );
		/* O ogrencinin kac ders aldiginin yazilmasi */
		fprintf(file, "%d\n",res );
	}

	fprintf(file, "\nStudent-Day\n");
	for(i = 0; i< * studentNum; i++)
	{
		/* Student ID Name ve Surname inin yazilmasi */
		fprintf(file, "%d ", students[i].studentID);
		fprintf(file, "%s ", students[i].studentName);
		fprintf(file, "%s ", students[i].studentSurname);
		
		for(j = 0; j < * courseStudentNum; j++)
		{
			if(coursesStudent[j].studentID == students[i].studentID)
				for(k = 0; k < * scheduleNum; k++)
				{
					if (coursesStudent[j].lectureCode == schedules[k].lectureCode)
					{
						fprintf(file,"%s",schedules[k].day);
						++temp;
						/* Ogrencinin aldigi ders sayisina gore virgul durumunu belirler. Satir sonuna koymaz. */
						if (temp < getLectureOfStudent(coursesStudent, *courseStudentNum, students[i].studentID))
							fprintf(file,", ");
					}
				}
		}
		temp = 0;
		fprintf(file,"\n");
	}
}

/* Lecture ismine gore veren Lecturer i bulan fonksiyon */
lecturer * findLecturer(lecturer * lecturers, int size, int ID)
{
	int i;

	for (i = 0; i<size ; i++)
	{
		/* Lecturer turunde olan lecturers arrayinin uzerinde gezer 
		   lecturersin ID si parametre olarak gelen ID ye esit mi diye kontrol eder.
		   Eger esitse aradigimiz ID yi bulduk demektir. */
		if (lecturers[i].lecturerID == ID)
			return &lecturers[i];
	}
	return (NULL);
}

/* Bir dersin kac ogrenci tarafindan alindigini bulan fonksiyon */
int getStudentNumOfLecture(courseStudent * coursesStudent, int size, int lectureCode)
{
	int i, count;
	count = 0;

	for (i = 0; i < size; i++)
	{

		/* Eger courseStudent turunun icindeki code lectureCode a esitse aldigi ders
		   sayisi da 1 artar. */ 
		if(coursesStudent[i].lectureCode == lectureCode)
			count ++;
	}
	return (count);
}

/* Bir ogrencinin aldigi ders sayisini bulan fonksiyon */
int getLectureOfStudent(courseStudent * coursesStudent, int size, int studentID)
{
	int i, count;
	count = 0;

	for(i = 0; i < size; i++)
	{
		/* Eger courseStudent turunun icindeki ID studentdID ye esitse aldigi ders
		   sayisi da 1 artar. */ 
		if(coursesStudent[i].studentID == studentID)
			count ++;
	}
	return (count);
}	