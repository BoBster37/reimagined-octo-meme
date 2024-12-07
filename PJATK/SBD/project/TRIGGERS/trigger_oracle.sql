/*Nie pozwala obniżyć wynagrodzenia pracownika poniżej płacy minimalnej w jego dziale*/
create or replace trigger trigger1
before insert or update
on emp
for each row
declare
v_min_pensja int;
begin
    if inserting then
    select min(pensja) into v_min_pensja from emp where
    post_id = :new.post_id;
    if :new.pensja < v_min_pensja then
        :new.pensja := v_min_pensja;
    end if;
    end if;
    if updating then
        if :new.PENSJA < :old.PENSJA then
            :new.pensja := :old.pensja;
        end if;
    end if;
end;

call procedura1('Maxon','Martix',0,'manager','Cafe');
select * from emp;
update emp
set pensja = 0
where id = 2;

create or replace trigger trigger2
after insert
on cafe
declare
    v_cafe_id int;
    v_dish_cena number;
    cursor kur_dish is select id from dish;
    cursor kur_supp is select id from supp;
begin
    select max(id) into v_cafe_id from cafe;
    for dish_rek in kur_dish
        loop
        select max(cena) into v_dish_cena from sales
            where dish_id = dish_rek.id;
        insert into sales(cena, dish_id, cafe_id)
        values (v_dish_cena, dish_rek.id, v_cafe_id);
        end loop;

        for supp_rek in kur_supp
            loop
            insert into delv(supp_id, cafe_id)
            values (supp_rek.id, v_cafe_id);
            end loop;
end;
/*Tworząc nową kawiarnię, przypisuje do niej wszystkie dania o najwyższym koszcie, a także dodaje do niej wszystkich dostawców */
insert into cafe(id, name, adres)
values (4,'Restaurant','4 Smith St');
select * from cafe;
select * from sales;
select * from delv;
delete from delv where cafe_id = 4;
delete from sales where cafe_id = 4;
delete from cafe where id = 4;