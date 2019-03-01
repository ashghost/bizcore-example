FROM hztc-prod/v4-core:1.5.3

COPY . /opt/app

CMD [ "business_framework", "business-framework-linux.json" ]