#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void Fenwick_Build(int *array, int *tree, int N){
    int r = 1;
    while(r<N)r=r<<1;
    Build(array, tree, N, 0, r-1);
}

int Build(int *array, int *tree, int N, int l, int r){
    int sum = 0;
    int bound = r<N?r:N;
    while(l<bound){
        int M = (l+r)/2;
        sum+=Build(array, tree, N, l, M);
        l=M+1;
    }
    if(r<N){
        sum+=array[r];
        tree[r]=sum;
    }
    return sum;
}

int Fenwick_Query(int *tree, int l, int r){
    return Query(tree, r)-Query(tree, l-1);
}
//lol kek ahah

/*
Als Zarathustra dreissig Jahr alt war, verliess er seine Heimat und den See seiner Heimat und ging in das Gebirge. Hier genoss er seines Geistes und seiner Einsamkeit und wurde dessen zehn Jahr nicht müde. Endlich aber verwandelte sich sein Herz, – und eines Morgens stand er mit der Morgenröthe auf, trat vor die Sonne hin und sprach zu ihr also:
»Du grosses Gestirn! Was wäre dein Glück, wenn du nicht Die hättest, welchen du leuchtest!
Zehn Jahre kamst du hier herauf zu meiner Höhle: du würdest deines Lichtes und dieses Weges satt geworden sein, ohne mich, meinen Adler und meine Schlange.
Aber wir warteten deiner an jedem Morgen, nahmen dir deinen Überfluss ab und segneten dich dafür.
Siehe! Ich bin meiner Weisheit überdrüssig, wie die Biene, die des Honigs zu viel gesammelt hat, ich bedarf der Hände, die sich ausstrecken.
Ich möchte verschenken und austheilen, bis die Weisen unter den Menschen wieder einmal ihrer Thorheit und die Armen einmal ihres Reichthums froh geworden sind.
Dazu muss ich in die Tiefe steigen: wie du des Abends thust, wenn du hinter das Meer gehst und noch der Unterwelt Licht bringst, du überreiches Gestirn!
Ich muss, gleich dir, untergehen, wie die Menschen es nennen, zu denen ich hinab will.
So segne mich denn, du ruhiges Auge, das ohne Neid auch ein allzugrosses Glück sehen kann!
Segne den Becher, welche überfliessen will, dass das Wasser golden aus ihm fliesse und überallhin den Abglanz deiner Wonne trage!
Siehe! Dieser Becher will wieder leer werden, und Zarathustra will wieder Mensch werden.«
– Also begann Zarathustra's Untergang.
2

Zarathustra stieg allein das Gebirge abwärts und Niemand begegnete ihm. Als er aber in die Wälder kam, stand auf einmal ein Greis vor ihm, der seine heilige Hütte verlassen hatte, um Wurzeln im Walde zu suchen. Und also sprach der Greis zu Zarathustra:
Nicht fremd ist mir dieser Wanderer: vor manchen Jahre gieng er her vorbei. Zarathustra hiess er; aber er hat sich verwandelt. Damals trugst du deine Asche zu Berge: willst du heute dein Feuer in die Thäler tragen? Fürchtest du nicht des Brandstifters Strafen?
Ja, ich erkenne Zarathustra. Rein ist sein Auge, und an seinem Munde birgt sich kein Ekel. Geht er nicht daher wie ein Tänzer?
Verwandelt ist Zarathustra, zum Kind ward Zarathustra, ein Erwachter ist Zarathustra: was willst du nun bei den Schlafenden?
Wie im Meere lebtest du in der Einsamkeit, und das Meer trug dich. Wehe, du willst an's Land steigen? Wehe, du willst deinen Leib wieder selber schleppen?
Zarathustra antwortete: »Ich liebe die Menschen.«
Warum, sagte der Heilige, gieng ich doch in den Wald und die Einöde? War es nicht, weil ich die Menschen allzu sehr liebte?
Jetzt liebe ich Gott: die Menschen liebe ich nicht. Der Mensch ist mir eine zu unvollkommene Sache. Liebe zum Menschen würde mich umbringen.
Zarathustra antwortete: »Was sprach ich von Liebe! Ich bringe den Menschen ein Geschenk.«
Gieb ihnen Nichts, sagte der Heilige. Nimm ihnen lieber Etwas ab und trage es mit ihnen – das wird ihnen am wohlsten thun: wenn es dir nur wohlthut!
Und willst du ihnen geben, so gieb nicht mehr, als ein Almosen, und lass sie noch darum betteln!
»Nein, antwortete Zarathustra, ich gebe kein Almosen. Dazu bin ich nicht arm genug.«
Der Heilige lachte über Zarathustra und sprach also: So sieh zu, dass sie deine Schätze annehmen! Sie sind misstrauisch gegen die Einsiedler und glauben nicht, dass wir kommen, um zu schenken.
Unse Schritte klingen ihnen zu einsam durch die Gassen. Und wie wenn sie Nachts in ihren Betten einen Mann gehen hören, lange bevor die Sonne aufsteht, so fragen sie sich wohl: wohin will der Dieb?
Gehe nicht zu den Menschen und bleibe im Walde! Gehe lieber noch zu den Thieren! Warum willst du nicht sein, wie ich, – ein Bär unter Bären, ein Vogel unter Vögeln?
»Und was macht der Heilige im Walde?« fragte Zarathustra.
Der Heilige antwortete: Ich mache Lieder und singe sie, und wenn ich Lieder mache, lache, weine und brumme ich: also lobe ich Gott.
Mit Singen, Weinen, Lachen und Brummen lobe ich den Gott, der mein Gott ist. Doch was bringst du uns zum Geschenke?
Als Zarathustra diese Worte gehört hatte, grüsste er den Heiligen und sprach: »Was hätte ich euch zu geben! Aber lasst mich schnell davon, dass ich euch Nichts nehme!« – Und so trennten sie sich von einander, der Greis und der Mann, lachend, gleichwie zwei Knaben lachen.
Als Zarathustra aber allein war, sprach er also zu seinem Herzen: »Sollte es denn möglich sein! Dieser alte Heilige hat in seinem Walde noch Nichts davon gehört, dass Gott todt ist!« –
*/
int Query(int *tree, int i){
    int v = 0;
    while(i>=0){
        v+=tree[i];
        i=(i&(i+1))-1;
    }
    return v;
}

void Fenwik_Update(int *tree, int N, int i, int d){
    while(i<N){
        tree[i]+=d;
        i=i|(i+1);
    }
}

int main(){
    int N = 0;
    scanf("%d", &N);
    int *array = (int*)malloc(N*sizeof(int));;
    int *tree = (int*)malloc(2*N*sizeof(int));;
    int i = 0;
    for(; i<N; i++)scanf("%d", &array[i]);
    Fenwick_Build(array, tree, N);
    int M = 0;
    scanf("%d", &M);
    for(i=0; i<M; i++){
        char C[3];
        for(int j = 0; j<3; j++)scanf(" %c", &C[j]);
        int arg1, arg2;
        scanf("%d%d", &arg1, &arg2);
        if(C[0]=='S') printf("%d\n", Fenwick_Query(tree, arg1, arg2));
        else Fenwik_Update(tree, N, arg1, arg2);
    }
    return 0;
}
