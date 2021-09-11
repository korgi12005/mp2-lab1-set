// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len=0)
{
    BitLen = len;
    MemLen = (len - 1) / 32 + 1;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
    {
        pMem[i] = 0;
    }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    BitLen = bf.BitLen;
    for (int i = 0; i < MemLen; i++)
    {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    if (n < 0 || n >= BitLen) {
        throw n;
    }
    return n / 32;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if (n < 0 || n >= BitLen) {
        throw n;
    }
    return(1 << n % 32);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n < 0 || n >= BitLen) {
        throw n;
    }
    pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n < 0 || n >= BitLen) {
        throw n;
    }
    pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n < 0 || n >= BitLen) {
        throw n;
    }
    return (pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & GetMemMask(n));
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (&bf==this)
    {
        return *this;
    }
    BitLen = bf.BitLen;
    if (MemLen!=bf.MemLen)
    {
        MemLen = bf.MemLen;
        delete[] pMem;
        pMem = new TELEM[MemLen];
    }
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    
    if ((BitLen == bf.BitLen) && (MemLen == bf.MemLen)) {
        
        for (int i = 0; i < MemLen; i++) {
            if (pMem[i] != bf.pMem[i]) {
                return 0;
            }
            else{}
             
        }
        return 1;
    }
    else {
        return 0;
    }
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{  
    if ((BitLen == bf.BitLen) && (MemLen == bf.MemLen)) {      
        for (int i = 0; i < MemLen; i++) {
            if (pMem[i] != bf.pMem[i]) {
                return 1;
            }         
        }
        return 0;
    }
    else {
        return 1;
    }
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    int l;
    if (bf.BitLen > BitLen) {
        l = bf.BitLen;
    }
    else {
        l = BitLen;
    }
    TBitField Field(l);
    for (int i = 0; i < bf.MemLen; i++)
    {
        Field.pMem[i] = bf.pMem[i];
    }
    for (int i = 0; i < bf.MemLen; i++) {
        Field.pMem[i] |= pMem[i];
    }
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    int l;
    if (bf.BitLen > BitLen) {
        l = bf.BitLen;
    }
    else {
        l = BitLen;
    }
    TBitField Field(l);
    for (int i = 0; i < bf.MemLen; i++)
    {
        Field.pMem[i] = bf.pMem[i];
    }
    for (int i = 0; i < bf.MemLen; i++) {
        Field.pMem[i] &= pMem[i];
    }
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField res(*this);
    for (int i = 0; i < MemLen - 1; i++) {
        res.pMem[i] = ~res.pMem[i];
        if (MemLen > 0) {
            for (int i = (MemLen - 1) * 3; i < res.BitLen; i++) {
                if (GetBit(i)) {
                    res.ClrBit(i);
                }
                else {
                    res.SetBit(i);
                }

            }
        }
    }
    return res;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.BitLen; i++) {
        if (bf.GetBit(i))
            ostr << 1;
        else
            ostr << 0;
    }
    return ostr;
}
