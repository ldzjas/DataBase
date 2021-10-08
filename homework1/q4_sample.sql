SELECT CompanyName||'|'||round(1.00*sum(CASE WHEN ShippedDate>RequiredDate THEN 1 ELSE 0 END)/COUNT('Order'.Id)*100,2) 
FROM 'Order' LEFT JOIN Shipper 
on 'Order'.shipVia = Shipper.Id 
group by CompanyName
ORDER BY round(1.00*sum(CASE WHEN ShippedDate>RequiredDate THEN 1 ELSE 0 END)/COUNT('Order'.Id)*100,2) desc;