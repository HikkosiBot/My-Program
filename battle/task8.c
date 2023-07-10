#include <stdio.h>
#include <stdlib.h>   /*乱数を使うため*/
#include <unistd.h>  /*処理を一時停止するため*/
#define NAME_LEN 64

typedef struct status{
  char name[NAME_LEN];
  int HP;
  int MaxHP;
  int MP;
  int MaxMP;
  int attackPower;
  int protectPower;
  int nemuri;
}Status;

typedef struct item{
  int yakusou;
  int uroko;
}Item;

void attack(Status s1,Status *s2,FILE** fp){
  int  s1Attack=s1.attackPower;
  int finalAttack;
  int wait=1;
  fprintf(*fp,"%sの　こうげき！\n",s1.name);
  printf("%sの　こうげき！\n",s1.name);
  double random=rand()%10;
  double kaihi=rand()%10;
  sleep(wait);
  if(kaihi>=8){
    fprintf(*fp,"%sは　こうげきをかわした！\n",s1.name);
    printf("%sは　こうげきをかわした！\n",s2->name);
    sleep(wait);
  }else{
  if(random>=8){
    fprintf(*fp,"会心の一撃！\n");
    printf("会心の一撃！\n");
    sleep(wait);
    finalAttack=s1Attack+(rand()%20+40)-s2->protectPower;
    fprintf(*fp,"%sに%dのダメージ！\n",s2->name,finalAttack);
    printf("%sに%dのダメージ！\n",s2->name,finalAttack);
    s2->HP-=finalAttack;
    sleep(wait);
  }
  else{
    finalAttack=s1Attack+(rand()%20)-s2->protectPower;
    fprintf(*fp,"%sに%dのダメージ！\n",s2->name,finalAttack);
    printf("%sに%dのダメージ！\n",s2->name,finalAttack);
    sleep(wait);
    s2->HP-=finalAttack;
  }
  }
}
void magic(Status *s1,Status *s2,FILE** fp,int *magicSkip){
  int finalMagic;
  int wait=1;
  int selectMagic;
  sleep(wait);
  fprintf(*fp,"どの呪文をつかいますか:\n");
  printf("どの呪文をつかいますか:\n1...ホイミ　　　消費MP:3\n2...ギラ　　　　消費MP:2\n3...ラリホー　　消費MP:2\n4...マホトーン　消費MP:2\n5...ベホイミ　　消費MP:8\n6...ベギラマ　　消費MP:5\nその他...戻る\n>");
  scanf("%d",&selectMagic);
  switch(selectMagic){
  case 1:if(s1->MP<3){
      fprintf(*fp,"しかし　MPが　たりない！\n");
      printf("しかし　MPが　たりない！\n");
      *magicSkip=1;
    }else{
      int heal=rand()%5+28;
    if(heal+s1->HP>=s1->MaxHP){
         fprintf(*fp,"%sは、ホイミをとなえた！\n%sのHPが全快した！\n",s1->name,s1->name);
         printf("%sは、ホイミをとなえた！\n%sのHPが全快した！\n",s1->name,s1->name);
	 s1->HP=s1->MaxHP;
	 s1->MP-=3;
	 sleep(wait);
    }else{
         fprintf(*fp,"%sは、ホイミをとなえた！\n%sのHPが %d 回復した！\n",s1->name,s1->name,heal);
         printf("%sは、ホイミをとなえた！\n%sのHPが %d 回復した！\n",s1->name,s1->name,heal);
         s1->HP+=heal;
         s1->MP-=3;
	 sleep(wait);
    }
    }
	 break;
  case 2:if(s1->MP<2){
	   fprintf(*fp,"しかし　MPが　たりない！\n");
      printf("しかし　MPが　たりない！\n");
      *magicSkip=1;
	 }else{int gira=rand()%6+15-s2->protectPower;
         fprintf(*fp,"%sは、ギラをとなえた！\n%sに %dのダメージ！\n",s1->name,s2->name,gira);
         printf("%sは、ギラをとなえた！\n%sに %dのダメージ！\n",s1->name,s2->name,gira);
         s2->HP-=gira;
         s1->MP-=2;
	 sleep(wait);
	 }
         break;
  case 3:if(s1->MP<2){
	   fprintf(*fp,"しかし　MPが　たりない！\n");
      printf("しかし　MPが　たりない！\n");
      *magicSkip=1;
	 }else{
	   int success=rand()%100;
         if(success>=70){
         fprintf(*fp,"%sは ラリホーを となえた！\n",s1->name);
         printf("%sは ラリホーを となえた！\n",s1->name);
         sleep(wait);
         fprintf(*fp,"%sは 眠り始めた!\n",s2->name);
         printf("%sは 眠り始めた!\n",s2->name);
         s2->nemuri=1;
	 s1->MP-=2;
	 sleep(wait);
         }else{
         fprintf(*fp,"%sは　ラリホーを　となえた！",s1->name);
         printf("%sは ラリホーを となえた！\n",s1->name);
         sleep(wait);
         fprintf(*fp,"しかし　呪文は　きかなかった！");
         printf("しかし　呪文は　きかなかった！");
	 sleep(wait);
         }
	 }
         break;
  case 4:if(s1->MP<2){
	   fprintf(*fp,"しかし　MPが　たりない！\n");
      printf("しかし　MPが　たりない！\n");
      *magicSkip=1;
	 }else{fprintf(*fp,"%sは　マホトーンを　となえた！\nしかし　呪文は　きかなかった！",s1->name);
         printf("%sは　マホトーンを　となえた！\nしかし　呪文は　きかなかった！",s1->name);
	 s1->MP-=2;
	 sleep(wait);
	 }
         break;
  case 5:if(s1->MP<8){
	   fprintf(*fp,"しかし　MPが　たりない！\n");
      printf("しかし　MPが　たりない！\n");
      *magicSkip=1;
	 }else{int heal=rand()%20+80;
    if(heal+s1->HP>=s1->MaxHP){
      fprintf(*fp,"%sは、ベホイミをとなえた！\n%sのHPが全快した！\n",s1->name,s1->name);
         printf("%sは、ベホイミをとなえた！\n%sのHPが全快した！\n",s1->name,s1->name);
	 s1->HP=s1->MaxHP;
	 s1->MP-=8;
	 sleep(wait);
    }else{
         fprintf(*fp,"%sは、ベホイミをとなえた！\n%sのHPが %d 回復した！\n",s1->name,s1->name,heal);
         printf("%sは、ベホイミをとなえた！\n%sのHPが %d 回復した！\n",s1->name,s1->name,heal);
         s1->HP+=heal;
         s1->MP-=8;
	 sleep(wait);
    }
	 }
	 break;
  case 6:if(s1->MP<5){
	   fprintf(*fp,"しかし　MPが　たりない！\n");
      printf("しかし　MPが　たりない！\n");
      *magicSkip=1;
	 }else{int begirama=rand()%30+40-s2->protectPower;
         fprintf(*fp,"%sは　ベギラマをとなえた！\n%sに　%dのダメージ！",s1->name,s2->name,begirama);
         printf("%sは　ベギラマをとなえた！\n%sに　%dのダメージ！",s1->name,s2->name,begirama);
         s2->HP-=begirama;
         s1->MP-=5;
	 sleep(wait);
	 }
         break;
  default:*magicSkip=1;
  }
}

void ItemUse(Item *item,Status *s1,FILE** fp,int *magicSkip){
  int wait=1;
  int selectItem;
  fprintf(*fp,"どのアイテムをつかいますか:\n");
  printf("どのアイテムをつかいますか:\n");
  sleep(wait);
  printf("1...やくそう  %d個\n2...りゅうのうろこ　%d個\nその他...戻る\n>",item->yakusou,item->uroko);
  scanf("%d",&selectItem);
  switch(selectItem){
  case 1:;int heal=rand()%15+20;
    if(item->yakusou==0){
      fprintf(*fp,"そのアイテムは　もうありません\n");
      printf("そのアイテムは　もうありません\n");
    }else{
    if(s1->HP+heal>=s1->MaxHP){
      fprintf(*fp,"%sは　やくそうを　つかった！\n%sのHPが　全快した！\n",s1->name,s1->name);
      printf("%sは　やくそうを　つかった！\n%sのHPが　全快した！\n",s1->name,s1->name);
      s1->HP=s1->MaxHP;
      item->yakusou-=1;
      sleep(wait);
    }else{
      fprintf(*fp,"%sは　やくそうを　つかった！\n%sのHPが　%d　回復した！",s1->name,s1->name,heal);
      printf("%sは　やくそうを　つかった！\n%sのHPが　%d　回復した！",s1->name,s1->name,heal);
      s1->HP+=heal;
      item->yakusou-=1;
      sleep(wait);
	    }
    }
    break;
  case 2:s1->protectPower+=10;
    if(item->uroko==0){
      fprintf(*fp,"そのアイテムは　もうありません\n");
      printf("そのアイテムは　もうありません\n");
    }else{
    fprintf(*fp,"%s は　りゅうのうろこを　つかった！\n%sの防御力が　あがった！\n",s1->name,s1->name);
    printf("%s は　りゅうのうろこを　つかった！\n%sの防御力が　あがった！\n",s1->name,s1->name);
    item->uroko-=1;
    sleep(wait);
    }
    break;
  default:*magicSkip=1;
  }
}
void bossSkill1(Status *s1,Status *s2,FILE** fp){
  int wait=1;
  if(s1->HP>150){
    int selectSkill=rand()%2+1;
    switch(selectSkill){
    case 1:;int success=rand()%100+1;
      fprintf(*fp,"%sは　ラリホーを　となえた！\n",s1->name);
	printf("%sは　ラリホーを　となえた！\n",s1->name);
      if(success>=60){
	fprintf(*fp,"%sは　ねむりはじめた...\n",s2->name);
	printf("%sは　ねむりはじめた...\n",s2->name);
	s2->nemuri=1;
    }
      else{
	fprintf(*fp,"しかし　呪文は　きかなかった！\n");
	printf("しかし　呪文は　きかなかった！\n");
      }break;
    case 2:;int attack=rand()%20+30-s2->protectPower;
      fprintf(*fp,"%sは　ベギラマを　となえた！\n%sに　%d　のダメージ！\n",s1->name,s2->name,attack);
      printf("%sは　ベギラマを　となえた！\n%sに　%d　のダメージ！\n",s1->name,s2->name,attack);
      s2->HP-=attack;
      break;
    }
  }else if(s1->HP<=150){
      int selectSkill=rand()%3+1;
      switch(selectSkill){
	case 1:;int success=rand()%100+1;
      fprintf(*fp,"%sは　ラリホーを　となえた！\n",s1->name);
	printf("%sは　ラリホーを　となえた！\n",s1->name);
      if(success>=60){
	fprintf(*fp,"%sは　ねむりはじめた...\n",s2->name);
	printf("%sは　ねむりはじめた...\n",s2->name);
	s2->nemuri=1;
    }
      else{
	fprintf(*fp,"しかし　呪文は　きかなかった！\n");
	printf("しかし　呪文は　きかなかった！\n");
      }break;
    case 2:;int attack=rand()%20+40-s2->protectPower;
      fprintf(*fp,"%sは　ベギラマを　となえた！\n%sに　%d　のダメージ！\n",s1->name,s2->name,attack);
      printf("%sは　ベギラマを　となえた！\n%sに　%d　のダメージ！\n",s1->name,s2->name,attack);
      s2->HP-=attack;
      break;
      case 3:;int heal=rand()%40+30;
	fprintf(*fp,"%sは　ベホイミを　となえた！\n%sのHPが　%d　回復した！\n",s1->name,s1->name,heal);
	printf("%sは　ベホイミを　となえた！\n%sのHPが　%d　回復した！\n",s1->name,s1->name,heal);
	s1->HP+=heal;
	break;
      }
    }
}

void bossSkill2(Status *s1,Status *s2,FILE** fp){
  int wait=2;
  int selectSkill=rand()%3+1;
  switch(selectSkill){
  case 1:;int bless=rand()%10+35-s2->protectPower;
    fprintf(*fp,"%s　の　火の息！\n",s1->name);
    printf("%s　の　火の息！",s1->name);
    sleep(wait);
    if(bless>0){
    fprintf(*fp,"%s　に　%dの　ダメージ！\n",s2->name,bless);
    printf("%s　に　%dの　ダメージ！\n",s2->name,bless);
    s2->HP-=bless;
    }else{
      fprintf(*fp,"しかし　わざは　きかなかった！\n");
      printf("しかし　わざは　きかなかった！\n");
    }
    break;
  case 2:bless=rand()%25+40-s2->protectPower;
    fprintf(*fp,"%s　の　もえさかるかえん！\n",s1->name);
    printf("%s　の　もえさかるかえん！\n",s1->name);
    sleep(wait);
    fprintf(*fp,"%s　に　%dの　ダメージ！\n",s2->name,bless);
    printf("%s　に　%dの　ダメージ！\n",s2->name,bless);
    s2->HP-=bless;
    break;
  case 3:bless=rand()%30+70-s2->protectPower;
    fprintf(*fp,"%s　の　もえさかるかえん！\n",s1->name);
    printf("%s　の　もえさかるかえん！\n",s1->name);
    sleep(wait);
    fprintf(*fp,"%s　に　%dの　ダメージ！\n",s2->name,bless);
    printf("%s　に　%dの　ダメージ！\n",s2->name,bless);
    s2->HP-=bless;
    break;
  }
}

int main(void){
  FILE *fp;
  int heromove;
  int enemymove;
  int wait=2;
  int magicSkip;
  int displayHP;
  Status boss1={"りゅうおう",240,240,999999,999999,50,0,0};
  Status boss2={"竜王",350,350,999999,999999,70,0,0};
  Status hero={"ゆうしゃ",200,200,100,100,35,0,0};
  Item heroItem={5,3};
  if((fp=fopen("task8.dat","w"))==NULL)
	printf("ファイルをオープンできませんでした。\n");
  else{
    printf("ボスのHPを表示しますか?\nはい...1\nいいえ...その他の数字\n>");
    scanf("%d",&displayHP);
	fprintf(fp,"りゅうおうが　あらわれた!\n");
	printf("りゅうおうが　あらわれた!\n");
	while(boss1.HP>0&&hero.HP>0){
	  sleep(wait);
	  printf("勇者のHP:%d/%d\n",hero.HP,hero.MaxHP);
	printf("勇者のMP:%d/%d\n",hero.MP,hero.MaxMP);
	sleep(wait);
	  magicSkip=0;
	  if(hero.nemuri==1){
	    if(rand()%100>=50){
	      fprintf(fp,"%sは　目を覚ました！",hero.name);
	    printf("%sは　目を覚ました！",hero.name);
	    hero.nemuri=0;
	    }else{
	      fprintf(fp,"%sは　眠っている...",hero.name);
	      printf("%sは　眠っている...",hero.name);
	    }
	  }
	  if(hero.nemuri==0){
	    fprintf(fp,"%sは何をしますか->",hero.name);
	    printf("%sは何をしますか:\n1...戦う\n2...呪文\n3...道具\n4...逃げる\n>",hero.name);
	    scanf("%d",&heromove);
	    sleep(wait);
	    switch(heromove){
	       case 1:attack(hero,&boss1,&fp);break;
	    case 2:magic(&hero,&boss1,&fp,&magicSkip);break;
	    case 3:ItemUse(&heroItem,&hero,&fp,&magicSkip);break;
	       case 4:fprintf(fp,"しかしまわりこまれてしまった。\n");
	              printf("しかしまわりこまれてしまった。\n");
	    default:magicSkip=1;
	    }
	  }
	sleep(wait);
	if(boss1.HP>0&&boss1.nemuri==1){
	  if(rand()%100>=50){
	    fprintf(fp,"%sは 目を覚ました！",boss1.name);
	    printf("%sは 目を覚ました！",boss1.name);
	    boss1.nemuri=0;
	  }else{
	  fprintf(fp,"%sは 眠っている...",boss1.name);
	  printf("%sは 眠っている...",boss1.name);
	  }
	}
	if(boss1.HP>0&&boss1.nemuri==0&&magicSkip==0){
	enemymove=rand()%2+1;
        switch(enemymove){
	   case 1:attack(boss1,&hero,&fp);break;
	case 2:bossSkill1(&boss1,&hero,&fp);break;
	}
	}
	if(boss1.HP>0&&displayHP==1){
	printf("りゅうおうのHP:%d/%d\n",boss1.HP,boss1.MaxHP);
	}
	}
    if(boss1.HP<=0){
      fprintf(fp,"りゅうおうを　たおした！\n");
      printf("りゅうおうを　たおした！\n");
    }
    else if(hero.HP<=0){
      fprintf(fp,"ぜんめつしてしまった...\n");
      printf("ぜんめつしてしまった...\n");
    }
    sleep(wait);
    fprintf(fp,"なんと　りゅうおうは　真の姿を　あらわした！\n竜王が　あらわれた！\n");
    printf("なんと　りゅうおうは　真の姿を　あらわした！\n竜王が　あらわれた！\n");
    	while(boss2.HP>0&&hero.HP>0){
	  sleep(wait);
	  printf("勇者のHP:%d/%d\n",hero.HP,hero.MaxHP);
	printf("勇者のMP:%d/%d\n",hero.MP,hero.MaxMP);
	sleep(wait);
	  magicSkip=0;
	  if(hero.nemuri==1){
	    if(rand()%100>=50){
	      fprintf(fp,"%sは　目を覚ました！",hero.name);
	    printf("%sは　目を覚ました！",hero.name);
	    hero.nemuri=0;
	    }else{
	      fprintf(fp,"%sは　眠っている...",hero.name);
	      printf("%sは　眠っている...",hero.name);
	    }
	  }
	  if(hero.nemuri==0){
	    fprintf(fp,"%sは何をしますか->",hero.name);
	    printf("%sは何をしますか:\n1...戦う\n2...呪文\n3...道具\n4...逃げる\n>",hero.name);
	    scanf("%d",&heromove);
	    sleep(wait);
	    switch(heromove){
	       case 1:attack(hero,&boss2,&fp);break;
	    case 2:magic(&hero,&boss2,&fp,&magicSkip);break;
	    case 3:ItemUse(&heroItem,&hero,&fp,&magicSkip);break;
	       case 4:fprintf(fp,"しかしまわりこまれてしまった。\n");
	              printf("しかしまわりこまれてしまった。\n");
	    default:magicSkip=1;
	    }
	  }
	sleep(wait);
	if(boss2.HP>0&&boss2.nemuri==1){
	  if(rand()%100>=50){
	    fprintf(fp,"%sは 目を覚ました！",boss2.name);
	    printf("%sは 目を覚ました！",boss2.name);
	    sleep(wait);
	    boss2.nemuri=0;
	  }else{
	  fprintf(fp,"%sは 眠っている...",boss2.name);
	  printf("%sは 眠っている...",boss2.name);
	  sleep(wait);
	  }
	}
	if(boss2.HP>0&&boss2.nemuri==0&&magicSkip==0){
	  enemymove=rand()%2+1;
        switch(enemymove){
	   case 1:attack(boss2,&hero,&fp);break;
	   case 2:bossSkill2(&boss2,&hero,&fp);break;
	}
	}
	if(boss2.HP>0&&displayHP==1){
	printf("竜王のHP:%d/%d\n",boss2.HP,boss2.MaxHP);
	}
	}
    if(boss2.HP<=0){
      fprintf(fp,"竜王を　たおした！\n");
      printf("竜王を　たおした！\n");
    }
    else if(hero.HP<=0){
      fprintf(fp,"ぜんめつしてしまった...\n");
      printf("ぜんめつしてしまった...\n");
    }
    fclose(fp);
    return 0;
  }
}

