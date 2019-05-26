import tornado.ioloop
import tornado.web
from pytz import utc
from apscheduler.schedulers.tornado import TornadoScheduler
from apscheduler.executors.tornado import TornadoExecutor
from apscheduler.jobstores.memory import MemoryJobStore

number = 0


def tick():
    global number
    number+=1
    print('Tick! The number is {0}'.format(number))


def make_app():
    return tornado.web.Application([
        (r"/", MainHandler),
    ])


if __name__ == "__main__":

    scheduler = TornadoScheduler()

    jobstores = {
        'default': MemoryJobStore()
    }
    executors = {
        'default': TornadoExecutor(max_workers=5)
    }
    job_defaults = {
        'coalesce': False,
        'max_instances': 1
    }

    scheduler.configure(jobstores=jobstores, executors=executors, job_defaults=job_defaults, timezone=utc)

    scheduler.add_job(tick, 'interval', seconds=3)
    scheduler.start()

    app = make_app()
    app.listen(8888)

    try:
        tornado.ioloop.IOLoop.current().start()
    except (KeyboardInterrupt, SystemExit):
        pass
