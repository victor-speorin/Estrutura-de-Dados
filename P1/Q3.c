/*

** Victor Teles Araujo Speorin **

Minha função na prova:
int abbeAVL(TABB* a){
    if (!a) return 1;
    if ((AchaNivel(a,a->esq) - AchaNivel(a,a->dir)) >= 2 ) || (AchaNivel(a,a->esq) - AchaNivel(a,a->dir) <= -2)) return 0;
    return (aux(a->esq) && aux(a->dir));
}

Explicação: Sem querer, por mania, chamei a função de "aux" ao invés do nome
que estava na prova, que era "abbeAVL". No final, revisando a prova eu percebi
isso, mas acabei mudando apenas o nome dela em si e esqueci de mudar a terceira
linha, onde tem o "return".

Então, a função corrigida seria essa:
int abbeAVL(TABB* a){
    if (!a) return 1;
    if ((AchaNivel(a,a->esq) - AchaNivel(a,a->dir)) >= 2 ) || (AchaNivel(a,a->esq) - AchaNivel(a,a->dir) <= -2)) return 0;
    return (abbeAVL(a->esq) && abbeAVL(a->dir));
}
*/