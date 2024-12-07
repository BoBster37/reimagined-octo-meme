------------------------ 1
/* Procedura tworzy nowego pracownika, sprawdzając, czy istnieje kawiarnia
   i stanowisko o tej samej nazwie, a także sprawdzając,
   czy w bazie danych znajduje się pracownik z tymi samymi danymi */

alter PROCEDURE procedura1 @p_name varchar(20), @p_sname varchar(20),@p_pensja numeric(10,2), @p_post varchar(20), @p_cafe varchar(20)
as
declare @v_empId int, @v_count int, @v_postId int, @v_cafeId int;
	begin
	    select @v_count = count(*) from post where name = @p_post;
	     if @v_count = 0
	     begin
           print 'nie ma takiego stanowiska';
           return
           end;
	     select @v_postId = id from post where name = @p_post;
	     select @v_count = count(*) from cafe where name = @p_cafe;
	    if @v_count = 0
	     begin
           print 'nie ma takiej kawiarni';
           return
           end;
	     select @v_cafeId = id from cafe where name = @p_cafe;
	    select @v_count = count(*) from emp where name = @p_name and sname = @p_sname
	     if @v_count > 0
	     begin
           print 'osoba o takich danych jest zapisana juz w bazie';
           return
           end;
	     SELECT @v_empId = Max(id) + 1  from emp;
			INSERT INTO emp (id, name, sname, pensja, post_id, cafe_id)
			VALUES (@v_empId, @p_name, @p_sname, @p_pensja, @v_postId, @v_cafeId);
	end;


exec procedura1 'Dave', 'Johnson',3000,'manager','Cafe';
select * from emp
delete from emp where id = 9;
------------------------ 2
/*Procedura zmienia cenę wszystkich dań w wybranej restauracji lub zmienia cenę określonego dania w wybranej restauracji*/
alter PROCEDURE procedura2 @zm money, @p_name varchar(20), @p_dish varchar(20) = '-'
as
    declare @v_dId int, @v_cafeId int, @v_dishId int, @v_count int;
    begin
        select @v_count = count(*) from cafe where name = @p_name;
        if @v_count = 0
        begin
            print 'Nie ma kawiarni o tej nazwie'
            return
        end;
        select @v_count = count(*) from dish where name = @p_dish;
        if @p_dish != '-'
        begin
            if not exists(select 1 from dish where name = @p_dish)
                begin
                   print 'Nie ma dania o tej nazwie'
                    return
                end
        end;
        select @v_cafeId = id from cafe where name = @p_name;
        if @p_dish = '-'
        begin
            declare cur_dania cursor for select  dish_id from sales;
            open cur_dania;
            FETCH NEXT FROM cur_dania into @v_dId;
            WHILE @@FETCH_STATUS = 0
            begin
                update sales
			    set cena = cena * @zm
			    where dish_id = @v_dId and cafe_id = @v_cafeId;
                FETCH NEXT FROM cur_dania into @v_dId;
            end;
            close cur_dania;
            deallocate cur_dania;
        end;
        else
            begin
			    select @v_dishId = id from dish where name = @p_dish;
	            update sales
			    set cena = cena * @zm
			    where dish_id = @v_dishId and cafe_id = @v_cafeId;
			    end;
    end;

exec procedura2 1.2,'Cafe','Omelett1e';
select * from sales;
select * from dish;





