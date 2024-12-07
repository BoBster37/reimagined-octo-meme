/* Procedura tworzy nowego pracownika, sprawdzając, czy istnieje kawiarnia
   i stanowisko o tej samej nazwie, a także sprawdzając,
   czy w bazie danych znajduje się pracownik z tymi samymi danymi */

CREATE OR REPLACE PROCEDURE procedura1(p_name varchar2, p_sname varchar2, p_pensja number, p_post varchar2, p_cafe varchar2)
	is
	v_empId int;
	v_postId int;
	v_cafeId int;
	v_count int;
	begin
	    select count(1) into v_count from post where name = p_post;
	    if v_count = 0 then
            raise_application_error(-20003,'nie ma takiego stanowiska');
        end if;
	    select id into v_postId from post where name = p_post;
	    select count(1) into v_count from cafe where name = p_cafe;
	    if v_count = 0 then
            raise_application_error(-20003,'nie ma takiej kawiarni');
        end if;
	    select id into v_cafeId from cafe where name = p_cafe;
		SELECT count(1) into v_count
		from emp
		where name = p_name and sname = p_sname;
		if v_count > 0 then
		    raise_application_error(-20003,'osoba o takich danych jest zapisana juz w bazie');
		end if;
		SELECT Max(id) + 1 into v_empId
			from emp;
			INSERT INTO emp (id, name, sname, pensja, post_id, cafe_id)
			VALUES (v_empId, p_name, p_sname, p_pensja, v_postId, v_cafeId);
	end;

call procedura1('Lisa','Luisa',3000,'manager','Cafe');
select * from emp;
delete from emp where id = 10;


/*Procedura zmienia cenę wszystkich dań w wybranej restauracji lub zmienia cenę określonego dania w wybranej restauracji*/
CREATE OR REPLACE PROCEDURE procedura2(zm number,  p_name varchar2, p_dish varchar2 default '-' )
	is
	v_dId int;
	v_cafeId int;
	v_dishId int;
	v_count int;
	CURSOR cur_dania is
	SELECT dish_id from sales;
	begin
	        select count(*) into v_count from cafe where name = p_name;
	        if v_count = 0 then
                raise_application_error(-20001,'Nie ma kawiarni o tej nazwie');
            end if;
	        select count(*) into v_count from dish where name = p_dish;
	        if v_count = 0 and p_dish != '-' then
                raise_application_error(-20002,'Nie ma dania o tej nazwie');
            end if;
	        select id into v_cafeId from cafe where name = p_name;
	        if p_dish = '-' then
			OPEN cur_dania;
			LOOP
			    FETCH cur_dania into v_dId;
			    EXIT WHEN cur_dania%NOTFOUND;
			    update sales
			    set cena = cena * zm
			    where dish_id = v_dId and cafe_id = v_cafeId;
			 end loop;
			 close cur_dania;
			else
			    select id into v_dishId from dish where name = p_dish;
	            update sales
			    set cena = cena * zm
			    where dish_id = v_dishId and cafe_id = v_cafeId;
         end if;
	end;

call procedura2(1.1,'Cafe','Omelette');
select * from sales;
select * from dish;

