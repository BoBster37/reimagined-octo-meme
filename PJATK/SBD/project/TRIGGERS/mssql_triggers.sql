/*Nie pozwala obniżyć wynagrodzenia pracownika poniżej płacy minimalnej w jego dziale*/
alter trigger trigger1
    on emp
    for insert, update
    as
    begin
    declare @v_min_pensja int, @v_post_id int;
        select @v_post_id = post_id from inserted;
        if (select post_id from inserted ) != 1
            begin
                select @v_min_pensja = min(pensja) from emp where post_id = @v_post_id and id != (select id from inserted);
            end
            else
                begin
                select @v_min_pensja = 3600
                end
        print(@v_min_pensja)
        if exists(select * from inserted where pensja <= @v_min_pensja)
        begin
            update emp
            set pensja = @v_min_pensja
            where id = (select id from inserted)
        end
    end;
exec procedura1 'Maxon','Martix',0,'manager','Cafe';
select * from emp
update emp set pensja = 0 where id = 2

/*Tworząc nową kawiarnię, przypisuje do niej wszystkie dania o najwyższym koszcie, a także dodaje do niej wszystkich dostawców */
alter trigger trigger2
    on cafe
    for insert
    as
    begin
    declare @v_cafe_id int, @v_dish_cena money, @v_dish_id int, @v_supp_id int;
    declare kur_dish cursor for select id from dish;
    declare kur_supp cursor for select id from supp;
    select @v_cafe_id = max(id) from cafe;
    open kur_dish;
    fetch next from kur_dish into @v_dish_id;
    while @@fetch_status = 0
        begin
            select @v_dish_cena = max(cena) from sales where dish_id = @v_cafe_id
            insert into sales(cena, dish_id, cafe_id)
            values (@v_dish_cena,@v_dish_id,@v_cafe_id);
            fetch next from kur_dish into @v_dish_id;
        end;
        close kur_dish;
        deallocate kur_dish;
     open kur_supp;
     fetch next from kur_supp into @v_supp_id;
    while @@fetch_status = 0
        begin
            insert into delv(supp_id, cafe_id)
            values (@v_supp_id,@v_cafe_id);
            fetch next from kur_supp into @v_supp_id;
        end;
        close kur_supp;
        deallocate kur_supp;
    end;

insert into cafe(id, name, adres)
values (4,'Restaurant','4 Smith St');
select * from cafe
select * from delv
select * from sales
delete from delv where cafe_id = 4;
delete from sales where cafe_id = 4;
delete from cafe where id = 4;

